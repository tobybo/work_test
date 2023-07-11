import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

import math

class Graph:
    def __init__(self):
        print("show on web")
        # export MPLBACKEND=WebAgg
        # 设置 web 地址，默认只能通过 127.0.0.1 访问，那么在服务器上启动，其他机器就不能访问
        mpl.rcParams['webagg.address'] = "10.23.0.40"

    def showSingleAxes(self, x_list, y_list, ax):
        if not ax:
            fig, ax = plt.subplots()  # Create a figure containing a single axes.
        # ax.plot(x_list, y_list)  # Plot some data on the axes.
        self.drawLine(ax, x_list, y_list)

    def showSingleAxesMultiLine(self, x_list, dic, title, ax):
        if not ax:
            fig, ax = plt.subplots(figsize=(8, 6))  # Create a figure containing a single axes.
        if title:
            ax.set_title(title)
        self.drawMutilLine(ax, x_list, dic)

    # 单 figure
    def showMultiAxes(self, cpu_x_list, cpu_dic):
        num_axes = len(cpu_dic)
        column = 2
        rows = math.ceil(num_axes / column)
        fig, axs = plt.subplots(rows, column, figsize=(18, 25))
        count = 0
        row = 0
        col = 0
        for thread_name, y_list in cpu_dic.items():
            axs[row][col].set_title(thread_name)
            # axs[row][col].plot(cpu_x_list, y_list)
            self.drawLine(axs[row][col], cpu_x_list, y_list)
            col = col + 1
            if col == 2:
                row = row + 1
                col = 0

    # 获取轴数组
    def getAexsShare(self, row, col):
        fig, axs = plt.subplots(row, col, figsize=(9, 6 * row), sharex=True)
        fig.subplots_adjust(hspace=0)
        return axs

    def getAexs(self, row, col):
        fig, axs = plt.subplots(row, col, figsize=(18, 6 * row), gridspec_kw=dict(width_ratios=[10,8]))
        return axs

    # 多 figure
    def showMultiFigure(self, cpu_x_list, cpu_dic):
        for thread_name, y_list in cpu_dic.items():
            fig, ax = plt.subplots()
            ax.set_title(thread_name)
            # ax.plot(cpu_x_list, y_list)
            self.drawLine(ax, cpu_x_list, y_list)

    # 平均值柱状图
    def showBar(self, cpu_dic, title, ax):
        if not ax:
            fig, ax = plt.subplots(figsize=(10, 6))
        if title:
            ax.set_title(title)
        categories = [name.replace("sub", "sub\n") for name in cpu_dic.keys()]
        ax.bar(categories, [cpu_use for cpu_use in cpu_dic.values()])

    # 画线
    def drawLine(self, ax, x_list, y_list, name):
        # print("name: ", name)
        if len(x_list) == 0:
            ax.plot(y_list, label=name)
            ax.legend()
        else:
            ax.plot(x_list, y_list, label=name)
            ax.legend()


    # 画多条线
    def drawMutilLine(self, ax, x_list, dic):
        for name, y_list in dic.items():
            self.drawLine(ax, x_list, y_list, name)

    def show(self):
        plt.show()





