# PolygonDecomposer
Design and Analysis of Algorithms: Assignment 1




In this assignment we have implemented the decomposition algorithm MP1 as well as the merging algorithm as described in the paper:

Fernández, J., Cánovas, L., & Pelegrın, B. (2000). Algorithms for the decomposition of a polygon into  convex polygons. European Journal of Operational Research, 121(2), 330-342. https://doi.org/10.1016/S0377-2217(99)00033-8

The goal of the algorithm is to decompose any arbitrary simple polygon into a set of convex polygons, whose union gives the original polygon. The merging process reduces the size of the set for a better decomposition. However, optimality of the decomposition is still not guaranteed.


## Implementation

We have implemented the algorithm using the DCEL (Doubly Connected Edge List) data structure in C++. Reference was taken from:

https://www.cs.umd.edu/class/spring2020/cmsc754/Lects/lect10-dcel.pdf

The data structure defines undirected edges as pairs of directed half-edges. It allows up to keep track of individual faces as we create them in the decomposition, gives us a method to traverse the polygon, and keeps track of the positions of multiple edges coming out of a single point with respect to each other.

## Visualization

We visualize below what the algorithm produces for different test cases. We have shown the differences in the results before and after the merging process as well.


| Original Polygon | Before Merging | After Merging |
|------------------|----------------|---------------|
|         ![enter image description here](https://i.ibb.co/jGt4YQh/Whats-App-Image-2023-03-24-at-6-53-14-PM.jpg)         |         ![enter image description here](https://i.ibb.co/d7pxz9L/Whats-App-Image-2023-03-24-at-6-53-14-PM-1.jpg)       |         ![enter image description here](https://i.ibb.co/CVN2jZC/Whats-App-Image-2023-03-24-at-6-53-12-PM.jpg)      |
|        ![enter image description here](https://i.ibb.co/zZLHC2T/Whats-App-Image-2023-03-24-at-6-56-42-PM.jpg)          |        ![enter image description here](https://i.ibb.co/f8kg81N/Whats-App-Image-2023-03-24-at-6-56-41-PM.jpg)        |        ![enter image description here](https://i.ibb.co/CPXZCN5/Whats-App-Image-2023-03-24-at-6-56-43-PM.jpg)       |
|          ![enter image description here](https://i.ibb.co/VSQtYfZ/Whats-App-Image-2023-03-24-at-7-00-40-PM.jpg)        |        ![enter image description here](https://i.ibb.co/X3w8d2M/Whats-App-Image-2023-03-24-at-7-00-41-PM.jpg)        |         ![enter image description here](https://i.ibb.co/PmqcP2B/Whats-App-Image-2023-03-24-at-7-00-42-PM.jpg)      |



## Computational Results

We worked with a dataset which had maps of countries as polygons. For our Time analysis we have split the set into 6 categories mentioned below. 

| Vertices | Notches | MP1 Time (ms) | MP1 Polygons | Merging Time (ms) | Merged Polygons |
|------------------|----------------|---------------|---------------|---------------|---------------|
| 0 - 15 | (1.645161, 1.355197) | (0.353819, 0.144913) | (3.83871, 1.392762) | (0.002987, 0.004167)| (3.193548, 1.013882) |
|15 - 25 | (6.515152, 1.583533) | (0.370097, 0.054968) | (8.363636, 2.133339) | (0.004594, 0.001633)| (6.181818, 1.648002) |
|25 - 40 | (13.325, 2.515465) | (0.45422, 0.091522) | (14.925, 3.221622) | (0.005203, 0.001851)| (11.35, 2.402456) |
|40 - 60 | (21.32432, 3.822841) | (0.561424, 0.086225) | (24.18919, 4.489728) | (0.006805, 0.00186)| (17.86486, 3.575862) |
|60 - 100 | (33.56, 5.817216) | (0.71552, 0.119387) | (38, 8.539126) | (0.008304, 0.001914)| (28.08, 6.047865) |
|100 - 300 | (83.36364, 28.3241) | (1.9141, 0.871116) | (92.27273, 29.52657) | (0.017009, 0.004499)| (67.09091, 21.13033) |


Detailed computational data can be obtained from the following csv:

https://docs.google.com/spreadsheets/d/1B414KaTXBl74Txg14dLtQrlSfIXwlwYMle4JyDQFvgo/edit?usp=sharing

### MORE EXAMPLES

| Original Polygon | Before Merging | After Merging |
|------------------|----------------|---------------|
|         ![enter image description here](https://i.ibb.co/nBzmJXj/in.png)         |         ![enter image description here](https://i.ibb.co/4fkt8S9/output.png)       |         ![enter image description here](https://i.ibb.co/jV3cMDt/merged.png)      |
|![enter image description here](https://i.ibb.co/X3vd3KZ/in.png) |![enter image description here](https://i.ibb.co/484JSbq/output.png) |![enter image description here](https://i.ibb.co/gmZ4ZNC/merged.png)|
|![enter image description here](https://i.ibb.co/8xgxBKv/in.png)|![enter image description here](https://i.ibb.co/342Z83G/output.png)|![enter image description here](https://i.ibb.co/5hV83pk/merged.png)|

### Team Members
 - Anubhav Sharma
 - Sreeram Yerasani
 - Varun Vaddiraju
 - Rohith Paul