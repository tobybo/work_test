#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import sys

#  x = np.linspace(-1,1,50)
#  y = 2*x + 1
#
#  plt.plot(x,y)


def drawRoad(coords, filename):
    x_list = []
    y_list = []
    m_list = []
    n_list = []
    idx = 0
    i = 0
    lenth = len(coords)
    while i < lenth - 1:
        x_list.append(coords[i])
        y_list.append(coords[i + 1])
        m_list.append(int(coords[i]) - 10)
        n_list.append(int(coords[i + 1]) - 10)
        idx = idx + 1
        i = i + 2
        pass

    #  print(x_list)
    #  print(y_list)
    plt.plot(x_list, y_list, "")
    plt.savefig(filename)
    plt.show()
    pass



#  print(sys.argv[0])
#  print(len(sys.argv))

coord_list = sys.argv[2:]
filename = sys.argv[1]
drawRoad(coord_list, filename)

