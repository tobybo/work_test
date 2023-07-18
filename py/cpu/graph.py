# -*- coding: utf-8 -*-
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

import math

from util import *

class Graph:
    def __init__(self):
        ip = get_local_ip()
        print("show on web, ", ip)
        # export MPLBACKEND=WebAgg
        # 设置 web 地址，默认只能通过 127.0.0.1 访问，那么在服务器上启动，其他机器就不能访问
        mpl.rcParams['webagg.address'] = ip

    def showSingleAxes(self, x_list, y_list, ax):
        if not ax:
            fig, ax = plt.subplots()  # Create a figure containing a single axes.
        self.drawLine(ax, x_list, y_list)

    # @画单个坐标系，包含多条曲线
    # @x_list 横坐标数组
    # @dic <曲线名字, 曲线的纵坐标数组>
    # @title 坐标系名称
    # @ax 已存在的坐标系(可以先统一创建 n*2 的坐标系，然后依次填充内容)
    def showSingleAxesMultiLine(self, x_list, dic, title, ax):
        if not ax:
            fig, ax = plt.subplots(figsize=(8, 6))  # Create a figure containing a single axes.
        if title:
            ax.set_title(title)
        self.drawMutilLine(ax, x_list, dic)

    # 单 figure
    def showMultiAxes(self, x_list, dic):
        num_axes = len(dic)
        column = 2
        rows = math.ceil(num_axes / column)
        fig, axs = plt.subplots(rows, column, figsize=(18, 25))
        count = 0
        row = 0
        col = 0
        for thread_name, y_list in dic.items():
            axs[row][col].set_title(thread_name)
            self.drawLine(axs[row][col], x_list, y_list)
            col = col + 1
            if col == 2:
                row = row + 1
                col = 0

    # 获取轴数组
    def getAexsShare(self, row, col):
        fig, axs = plt.subplots(row, col, figsize=(9, 6 * row), sharex=True)
        fig.subplots_adjust(hspace=0)
        return axs

    # @创建指定 row 行 col 列的坐标系
    # @return 返回坐标系数组
    def getAexs(self, row, col):
        #fig, axs = plt.subplots(row, col, figsize=(18, 6 * row), gridspec_kw=dict(width_ratios=[10,8]))
        # layout{'constrained', 'compressed', 'tight', 'none', LayoutEngine, None}
        fig, axs = plt.subplots(row, col, figsize=(18, 8 * row),gridspec_kw=dict(width_ratios=[8,6]))
        fig.subplots_adjust(hspace=0.3)
        return axs

    # 多 figure
    def showMultiFigure(self, x_list, dic):
        for thread_name, y_list in dic.items():
            fig, ax = plt.subplots()
            ax.set_title(thread_name)
            self.drawLine(ax, x_list, y_list)

    # @平均值柱状图
    # @dic <柱形命名, 柱形纵坐标值>
    # @title 坐标系命名
    # @ax 已创建的坐标系
    # @rotation 柱形命名旋转角度(名字过长时适当倾斜)
    def showBar(self, dic, title, ax, rotation=0):
        if not ax:
            fig, ax = plt.subplots(figsize=(10, 6))
        if title:
            ax.set_title(title)
        categories = [name.replace("sub", "sub\n") for name in dic.keys()]
        rects = ax.bar(categories, [use for use in dic.values()])
        ax.bar_label(rects, padding=3, rotation=-55)
        ax.tick_params(axis='x', rotation=rotation)

    # @画单条曲线
    # @ax 已创建的坐标系
    # @x_list 横坐标数组
    # @y_list 纵坐标数组
    # @name 曲线名字
    def drawLine(self, ax, x_list, y_list, name):
        if len(x_list) == 0:
            ax.plot(y_list, label=name)
            ax.legend()
        else:
            ax.plot(x_list, y_list, label=name)
            ax.legend()


    # @画多条线
    # @ax 已创建的坐标系
    # @x_list 横坐标数组
    # @dic <曲线名字, 曲线的纵坐标数组>
    def drawMutilLine(self, ax, x_list, dic):
        for name, y_list in dic.items():
            self.drawLine(ax, x_list, y_list, name)

    # @启动网页服务器
    # 打开指定网址即可查看绘制内容
    def show(self):
        plt.show()





