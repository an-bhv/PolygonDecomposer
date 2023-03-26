import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

inputs = ["in", "output", "merged"]
for path in inputs:
	path1 = path + ".txt"
	path2 = path + ".png"
	with open(path1) as f:
		lines = f.readlines()

	xs, ys = [], []
	for line in lines:
		if line.strip() == "":
			plt.fill(xs, ys, color='w',edgecolor='black', linewidth=0.5)
			xs, ys = [], []
		else:
			if ',' not in line:
				continue
			x, y = map(float, line.split(','))
			xs.append(x)
			ys.append(y)
	plt.title(path)
	plt.fill(xs, ys, edgecolor='black', linewidth=0.5)
	plt.savefig(path2, dpi=1200, bbox_inches='tight', pad_inches=0.1)
	plt.show()
