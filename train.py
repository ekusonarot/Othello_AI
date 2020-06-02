import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np

IN_NUM = 128;
HID_1_NUM = 64;
HID_2_NUM = 64;
OUT_NUM = 1;

class Network(nn.Module):
	def __init__(self):
		super().__init__()
		self.IN_NUM = 128
		self.HID_1_NUM = 64  
		self.HID_2_NUM = 64
		self.OUT_NUM = 1
		self.FullyConnectLayer_1 = nn.Linear(self.IN_NUM, self.HID_1_NUM)
		self.FullyConnectLayer_2 = nn.Linear(self.HID_1_NUM, self.HID_2_NUM)
		self.FullyConnectLayer_3 = nn.Linear(self.HID_2_NUM, self.OUT_NUM)
	
	def forward(self, x):
		x = self.FullyConnectLayer_1(x)
		x = F.relu(x)
		x = self.FullyConnectLayer_2(x)
		x = F.relu(x)
		x = self.FullyConnectLayer_3(x)
		return x

	def to_text_weights(self, filename: str):
		with open(filename, 'w') as f:
			for child in self.children():
				f.write(self.tensor_weights(child.weight))
				f.write(self.tensor_weights(child.bias))

	@staticmethod
	def tensor_weights(t: torch.Tensor) -> str:
		return " ".join([str(w) for w in t.detach().numpy().ravel()]) + '\n'




