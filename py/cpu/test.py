from graph import *

#CPU_LOG_NAME = "temp.log"
CPU_DETAIL_NAME = "temp2.log"

#  x_list = []
#  y_list = []
#  f = open(CPU_LOG_NAME, "r")
#  for line in f:
#      coordinate = [int(x) for x in line.split()]
#      x_list.append(coordinate[0])
#      y_list.append(coordinate[1])
#  f.close()
#
#  gp = Graph()
#  gp.showSingleAxes(x_list, y_list)

gp = Graph()

#  -----------------------------------------------
#  统计各个线程 cpu 消耗，画到不同的坐标轴上
#  cpu_dic = {}
#  f = open(CPU_DETAIL_NAME, "r")
#  for line in f:
#      vals = line.split()
#      cpu_use = float(vals[0])
#      thread_name = vals[1]
#      if not cpu_dic.get(thread_name):
#          cpu_dic[thread_name] = []
#      cpu_dic[thread_name].append(cpu_use)
#
#  f.close()
#
#  gp.showMultiAxes([], cpu_dic)
#  gp.showMultiFigure([], cpu_dic)
#  -----------------------------------------------

#  -----------------------------------------------
#  统计各个线程 cpu 消耗，画到同一个坐标轴上
#  cpu_dic = {}
#  f = open(CPU_DETAIL_NAME, "r")
#  for line in f:
#      vals = line.split()
#      cpu_use = float(vals[0])
#      thread_name = vals[1]
#      if not cpu_dic.get(thread_name):
#          cpu_dic[thread_name] = []
#      cpu_dic[thread_name].append(cpu_use)
#
#  f.close()
#
#  gp.showSingleAxesMultiLine([], cpu_dic)
#  -----------------------------------------------

#  -----------------------------------------------
# 按 pidstat 统计的 Average 信息画图 @discard 改为自行计算
#  cpu_average_dic = {}
#  f = open(CPU_AVERAGE_NAME, "r")
#  for line in f:
#      vals = line.split()
#      cpu_use = float(vals[0])
#      thread_name = vals[1]
#      cpu_average_dic[thread_name] = cpu_use
#  f.close()
#
#  gp.showBar(cpu_average_dic)
#  -----------------------------------------------

#  -----------------------------------------------
#  统计各个线程 cpu_use flt rss ior iow thread_name

# 曲线图
"""
{
[cpu] = {
    [thread_name] = []
}

[flt] = {
    [thread_name] = []
}
}
"""
graph_cpu_dic = {
    "cpu": {},
    "flt": {},
    "rss": {},
    "ior": {},
    "iow": {},
}

# 平均值矩形图
"""
{
[cpu] = {
    [thread_name] = int
}

...
}
"""
bar_cpu_dic = {
    "cpu": {},
    "flt": {},
    "rss": {},
    "ior": {},
    "iow": {},
}

not_show_dic = {
    "ior": True,
}

def insertVal(name, what, val):
    if not graph_cpu_dic[what].get(name):
        graph_cpu_dic[what][name] = []
    graph_cpu_dic[what][name].append(val)
    if not bar_cpu_dic[what].get(name):
        bar_cpu_dic[what][name] = val
    else:
        bar_cpu_dic[what][name] = (bar_cpu_dic[what][name] * (len(graph_cpu_dic[what][name]) - 1) + val)/len(graph_cpu_dic[what][name])

f = open(CPU_DETAIL_NAME, "r")
for line in f:
    vals = line.split()
    if len(vals) == 0:
        continue
    # cpu_use flt rss ior iow thread_name
    cpu_use = float(vals[0])
    flt = float(vals[1])
    rss = float(vals[2])
    ior = float(vals[3])
    iow = float(vals[4])
    thread_name = vals[5]
    insertVal(thread_name, "cpu", cpu_use)
    insertVal(thread_name, "flt", flt)
    insertVal(thread_name, "rss", rss)
    insertVal(thread_name, "ior", ior)
    insertVal(thread_name, "iow", iow)

f.close()

# 1.0 左边曲线图 右边柱状图
#  for what, dic in graph_cpu_dic.items():
#      if not_show_dic.get(what):
#          continue
#      gp.showSingleAxesMultiLine([], dic, what)
#      gp.showBar(bar_cpu_dic[what], what)

# 2.0 画到同一个 figure 中，方便下载 [两张图，曲线和柱形分开并各自合并]
#  row = 0
#  for what, dic in graph_cpu_dic.items():
#      if not_show_dic.get(what):
#          continue
#      row = row + 1
#  axs1 = gp.getAexsShare(row, 1)
#  axs2 = gp.getAexsShare(row, 1)
#  row = 0
#  for what, dic in graph_cpu_dic.items():
#      if not_show_dic.get(what):
#          continue
#      gp.showSingleAxesMultiLine([], dic, what, axs1[row])
#      gp.showBar(bar_cpu_dic[what], what, axs2[row])
#      row = row + 1

# 2.0 画到同一个 figure 中，方便下载 [一张图]
row = 0
for what, dic in graph_cpu_dic.items():
    if not_show_dic.get(what):
        continue
    row = row + 1
axs = gp.getAexs(row, 2)
row = 0
for what, dic in graph_cpu_dic.items():
    if not_show_dic.get(what):
        continue
    gp.showSingleAxesMultiLine([], dic, what, axs[row][0])
    gp.showBar(bar_cpu_dic[what], what, axs[row][1])
    row = row + 1




#  -----------------------------------------------

gp.show()




