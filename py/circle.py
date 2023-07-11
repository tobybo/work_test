#!/usr/bin/python3

import matplotlib.pyplot as plt
from matplotlib.patches import Circle, Wedge, Polygon
from matplotlib.collections import PatchCollection
import numpy as np
import sys

#  x = np.linspace(-1,1,50)
#  y = 2*x + 1
#
#  plt.plot(x,y)


def drawCircle(count, filename, coords):
    an = np.linspace(0, 2 * np.pi, 100)
    fig, ax = plt.subplots(1, count)

    for k in range(count):
        sub_ax = ax[k];
        lenth = len(coords[k])
        i = 0
        while i < lenth - 2:
            x = float(coords[k][i])
            y = float(coords[k][i + 1])
            r = float(coords[k][i + 2])
            print(k, " ", count, " ", lenth, " ", i, "(",x,",",y,",",r,")")
            sub_ax.plot(x + r * np.cos(an), y + r * np.sin(an))
            sub_ax.axis('equal')
            i = i + 3

    #  print(x_list)
    #  print(y_list)
    fig.tight_layout()
    plt.savefig(filename)
    plt.show()
    pass



#  print(sys.argv[0])
#  print(len(sys.argv))

filename = sys.argv[1]
count = int(sys.argv[2])
old_count = count
loop_idx = 0
coord_list = []
while count > 0:
    num = int(sys.argv[3 + loop_idx])
    coords = sys.argv[3+loop_idx + 1:3+num+loop_idx+1]
    loop_idx = loop_idx + 1 + num
    coord_list.append(coords)
    count = count - 1

drawCircle(old_count, filename, coord_list)
