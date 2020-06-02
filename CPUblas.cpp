#include "CPUblas.hpp"
#include <cmath>


#ifdef USE_EIGEN
// Eigen helpers
template <typename T>
using EigenMatrixMap =
    Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>;
template <typename T>
using ConstEigenMatrixMap =
    Eigen::Map<const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>;

template <typename T>
using EigenVectorMap =
    Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, 1>>;
template <typename T>
using ConstEigenVectorMap =
    Eigen::Map<const Eigen::Matrix<T, Eigen::Dynamic, 1>>;
#endif


void gemm_nn(int M, int N, int K, float ALPHA, 
        const float *A, int lda, 
        const float *B, int ldb,
        float *C, int ldc)
{
    #pragma omp parallel for
    for(int i = 0; i < M; ++i){
        for(int k = 0; k < K; ++k){
            float A_PART = ALPHA*A[i*lda+k];
            for(int j = 0; j < N; ++j){
                C[i*ldc+j] += A_PART*B[k*ldb+j];
            }
        }
    }
}

void gemm_nt(int M, int N, int K, float ALPHA, 
        const float *A, int lda, 
        const float *B, int ldb,
        float *C, int ldc)
{
    #pragma omp parallel for
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            float sum = 0;
            for(int k = 0; k < K; ++k){
                sum += ALPHA*A[i*lda+k]*B[j*ldb + k];
            }
            C[i*ldc+j] += sum;
        }
    }
}

void gemm_tn(int M, int N, int K, float ALPHA, 
        const float *A, int lda, 
        const float *B, int ldb,
        float *C, int ldc)
{
    #pragma omp parallel for
    for(int i = 0; i < M; ++i){
        for(int k = 0; k < K; ++k){
            float A_PART = ALPHA*A[k*lda+i];
            for(int j = 0; j < N; ++j){
                C[i*ldc+j] += A_PART*B[k*ldb+j];
            }
        }
    }
}

void gemm_tt(int M, int N, int K, float ALPHA, 
        const float *A, int lda, 
        const float *B, int ldb,
        float *C, int ldc)
{
    #pragma omp parallel for
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            register float sum = 0;
            for(int k = 0; k < K; ++k){
                sum += ALPHA*A[i+k*lda]*B[k+j*ldb];
            }
            C[i*ldc+j] += sum;
        }
    }
}



void gemm_cpu(
        bool TA, bool TB,
        int M, int N, int K,
        float ALPHA, 
        const float *A, int lda, 
        const float *B, int ldb,
        float BETA,
        float *C, int ldc)
{
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            C[i*ldc + j] *= BETA;
        }
    }
    if(!TA && !TB) {
        gemm_nn(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    } else if(TA && !TB) {
        gemm_tn(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    } else if(!TA && TB) {
        gemm_nt(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    } else if(TA && TB) {
        gemm_tt(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
	}
}

void blas::dense(const int inputs,
	             const int outputs,
	             const std::vector<float>& input,
	             const std::vector<float>& weights,
	             std::vector<float>& output
) {
#ifndef USE_BLAS
	gemm_cpu(false, true,
	         1, outputs, inputs,
	         1,
	         input.data(), inputs,
	         weights.data(), inputs,
	         1, 
	         output.data(), outputs);
#else
#ifdef USE_OPENBLAS
	
    cblas_sgemv(CblasRowMajor, CblasNoTrans,
                // M     K
                outputs, inputs,
                1.0f, &weights[0], inputs,
                &input[0], 1,
                0.0f, &output[0], 1);
	

#endif
#ifdef USE_EIGEN
    EigenVectorMap<float> y(output.data(), outputs);
    y.noalias() =
        ConstEigenMatrixMap<float>(weights.data(),
                                   inputs,
                                   outputs).transpose()
        * ConstEigenVectorMap<float>(input.data(), inputs);

#endif
#endif
}


void blas::fixed_gemm(
	const int M, const int N, const int K,
	const float alpha, 
	const std::vector<float>& A, const int lda,
	const std::vector<float>& B, const int ldb,
	const float beta,
	std::vector<float>& C, const int ldc
) {
    // Weight shape (output, input, filter_size, filter_size)
    // 96 18 3 3
    // C←αAB + βC
    // outputs[96,19x19] = weights[96,18x3x3] x col[18x3x3,19x19]
    // M Number of rows in matrices A and C.
    // N Number of columns in matrices B and C.
    // K Number of columns in matrix A; number of rows in matrix B.
    // lda The size of the first dimention of matrix A; if you are
    // passing a matrix A[m][n], the value should be m.
    //    cblas_sgemm(CblasRowMajor, TransA, TransB, M, N, K, alpha, A, lda, B,
    //                ldb, beta, C, N);

#ifndef USE_BLAS
	gemm_cpu(false, false,
	         M, N, K,
	         alpha,
	         A.data(), lda,
	         B.data(), ldb,
	         beta, 
	         C.data(), ldc);
#else
#ifdef USE_OPENBLAS
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
	            M, N, K,
	            alpha,
	            &A[0], lda,
	            &B[0], ldb,
	            beta, 
	            &C[0], ldc);

#endif
#ifdef USE_EIGEN
    auto C_mat = EigenMatrixMap<float>(C.data(), N, M);
    C_mat.noalias() =
        ConstEigenMatrixMap<float>(B.data(), N, K)
        * ConstEigenMatrixMap<float>(A.data(), K, M);
#endif
#endif
}



void blas::winograd_gemm(
	const int set_U, const int set_V, const int set_M,
	const int M, const int N, const int K,
	const float alpha, 
	const std::vector<float>& A, const int lda,
	const std::vector<float>& B, const int ldb,
	const float beta,
	std::vector<float>& C, const int ldc
) {

#ifndef USE_BLAS
	gemm_cpu(true, false,
	         M, N, K,
	         alpha,
	         A.data()+set_U, lda,
	         B.data()+set_V, ldb,
	         beta, 
	         C.data()+set_M, ldc);
#else
#ifdef USE_OPENBLAS

    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans,
                M, N, K,
                alpha,
                &A[set_U], lda,
                &B[set_V], ldb,
                beta,
                &C[set_M], ldc);

#endif
#ifdef USE_EIGEN

    auto C_mat = EigenMatrixMap<float>(C.data() + set_M, N, M);
    C_mat.noalias() =
       ConstEigenMatrixMap<float>(B.data() + set_V, N, K)
        * ConstEigenMatrixMap<float>(A.data() + set_U, M, K).transpose();

#endif
#endif
}
