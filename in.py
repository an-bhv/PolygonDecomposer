import matplotlib.pyplot as plt
import numpy as np

with open("in.txt") as f:
    lines = f.readlines()

xs, ys = [], []
for line in lines:
    # print(line)
    if line.strip() == "":
        # Empty line indicates a new polygon
        plt.fill(xs, ys, color='w',edgecolor='black', linewidth=0.5)
        xs, ys = [], []
    else:
        # Check that line has at least two comma-separated values
        if ',' not in line:
            continue
        x, y = map(float, line.split(','))
        # print(x,y)
        xs.append(x)
        ys.append(y)

# print(xs,ys)

# Fill the last polygon
plt.fill(xs, ys, edgecolor='black', linewidth=0.5)

# # Add grid and set style to dotted
# plt.grid(linestyle=':')
# plt.gca().set_aspect('equal', adjustable='box')

# # Set axis limits with padding
# points = np.array(list(zip(xs, ys)))
# min_x, max_x = np.min(points, axis=0)[0], np.max(points, axis=0)[0]
# min_y, max_y = np.min(points, axis=0)[1], np.max(points, axis=0)[1]
# pad = 0.3
# plt.gca().set_xlim([67, 98])
# plt.gca().set_ylim([7, 37])

# Save the image as a tight figure with padding
plt.savefig('in.png', dpi=1200, bbox_inches='tight', pad_inches=0.1)

