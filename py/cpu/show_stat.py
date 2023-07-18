# -*- coding: utf-8 -*-
from graph import *

import os
from copy import deepcopy as copy

#CPU_LOG_NAME = "temp.log"
HOME_PATH = os.path.expanduser('~')
CPU_DETAIL_NAME = "{0}/stats/stats_cpu.log".format(HOME_PATH)
MSG_NUM_NAME = "{0}/stats/stats_msg.log".format(HOME_PATH)
MSG_DELAY_NAME = "{0}/stats/stats_delay.log".format(HOME_PATH)
OPTICK_NAME = "{0}/stats/stats_optick.log".format(HOME_PATH)

gp = Graph()

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
    #------------
    # "msg": {Pkg = [], Db = [], Tm = [], nBuf = [], Recv = []}
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

bar_extend = {
    "max_use_ms": {}, # 统计单次耗时最严重的前 15 条协议
}

not_show_msg = {
    "on_msg_signal": 1,
}

not_show_dic = {
    "ior": True,
}

rotation_x = {
}

def insertVal(name, what, val):
    if not graph_cpu_dic[what].get(name):
        graph_cpu_dic[what][name] = []
    graph_cpu_dic[what][name].append(val)
    if not bar_cpu_dic[what].get(name):
        bar_cpu_dic[what][name] = val
    else:
        bar_cpu_dic[what][name] = (bar_cpu_dic[what][name] * (len(graph_cpu_dic[what][name]) - 1) + val)/len(graph_cpu_dic[what][name])

def fillCpuInfo():
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


def fillMsgInfo():
    graph_cpu_dic["msg"] = {}
    bar_cpu_dic["msg"] = {}
    f = open(MSG_NUM_NAME, "r")
    for line in f:
        vals = line.split()
        if len(vals) == 0:
            continue
        # pkg db tm nbuf recv
        pkg = float(vals[0])
        db = float(vals[1])
        timer = float(vals[2])
        nbuf = float(vals[3])
        recv = float(vals[4])
        insertVal("Pkg", "msg", pkg)
        insertVal("Db", "msg", db)
        insertVal("Timer", "msg", timer)
        insertVal("nBuf", "msg", nbuf)
        insertVal("RecvPkg", "msg", recv)
    f.close()

def fillDelayInfo():
    keys = ["max_delay", "nmsg", "logic_ms", "parse_ms", "gc_ms"]
    for key in keys:
        graph_cpu_dic[key] = {}
        bar_cpu_dic[key] = {}
    f = open(MSG_DELAY_NAME, "r")
    for line in f:
        vals = line.split()
        if len(vals) != 6:
            continue
        # thread_name max_delay nmsg logic_ms parse_ms gc_ms
        thread_name = vals[0]
        if float(vals[1]) < 0:
            continue
        for i in range(len(keys)):
            insertVal(thread_name, keys[i], float(vals[i + 1]))
    f.close()

def fillOptickInfo():
    # 1. 先统计所有消息的数量， 总 use_ms，总 total_ms
    temp_stats = {}
    temp_ranks = {}
    total_stats = {}

    # 统计单次最高耗时用
    high_use_stats = {} # [rpc_name] = max_use_ms
    high_use_rank = []  # [rpc_name, ...] 依靠 high_use_stats 进行排序

    f = open(OPTICK_NAME, "r")
    for line in f:
        vals = line.split()
        if len(vals) == 0:
            continue
        thread_name, rpc_name, use_ms, total_ms = vals[0], vals[1], float(vals[2]), float(vals[3])
        if use_ms <= 0 or total_ms <= 0:
            continue
        if not temp_stats.get(thread_name):
            temp_stats[thread_name] = {}
            temp_ranks[thread_name] = []
            total_stats[thread_name] = {}
        thrd_stats = temp_stats[thread_name]
        if not thrd_stats.get(rpc_name):
            thrd_stats[rpc_name] = [0, 0]
            temp_ranks[thread_name].append(rpc_name)
            total_stats[thread_name][rpc_name] = []
        if not not_show_msg.get(rpc_name):
            if not high_use_stats.get(rpc_name):
                high_use_stats[rpc_name] = use_ms
                high_use_rank.append(rpc_name)
            high_use_stats[rpc_name] = max(use_ms, high_use_stats[rpc_name])
        thrd_stats[rpc_name][0] = thrd_stats[rpc_name][0] + use_ms
        thrd_stats[rpc_name][1] = thrd_stats[rpc_name][1] + total_ms
        total_stats[thread_name][rpc_name].append([use_ms, total_ms])

    high_use_rank.sort(reverse=True, key = lambda rpc_name: high_use_stats[rpc_name])
    for i in range(min(15, len(high_use_rank))):
        bar_extend["max_use_ms"][high_use_rank[i]] = high_use_stats[high_use_rank[i]]

    for thread_name, rank in temp_ranks.items():
        rank.sort(reverse=True, key = lambda rpc_name: temp_stats[thread_name][rpc_name][0])

    temp_ranks2 = copy(temp_ranks)

    for thread_name, rank in temp_ranks2.items():
        rank.sort(reverse=True, key = lambda rpc_name: temp_stats[thread_name][rpc_name][1])

    # 2. 每个线程画4张图
        # 前十的 use_ms 曲线图, 柱形图
        # 前十的 total_ms 曲线图, 柱形图
    for thread_name, rank in temp_ranks.items():
        graph_name1 = "use_ms-{0}".format(thread_name)
        graph_name2 = "total_ms-{0}".format(thread_name)
        rotation_x[graph_name1] = -55
        rotation_x[graph_name2] = -55
        graph_cpu_dic[graph_name1] = {}
        graph_cpu_dic[graph_name2] = {}
        bar_cpu_dic[graph_name1] = {}
        bar_cpu_dic[graph_name2] = {}
        for i in range(min(10, len(rank))):
            for v in total_stats[thread_name][rank[i]]:
                insertVal(rank[i], graph_name1, v[0])
                insertVal(rank[i], graph_name2, v[1])
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
fillCpuInfo()
fillMsgInfo()
fillDelayInfo()
fillOptickInfo()
row = 0
for what, dic in graph_cpu_dic.items():
    if not_show_dic.get(what) or len(bar_cpu_dic[what]) == 0:
        continue
    row = row + 1

for title, rank in bar_extend.items():
    if len(rank) == 0:
        continue
    row = row + 1

axs = gp.getAexs(row, 2)
row = 0
for what, dic in graph_cpu_dic.items():
    if not_show_dic.get(what) or len(bar_cpu_dic[what]) == 0:
        continue
    gp.showSingleAxesMultiLine([], dic, what, axs[row][0])
    gp.showBar(bar_cpu_dic[what], what, axs[row][1], rotation_x.get(what))
    row = row + 1

for title, rank in bar_extend.items():
    if len(rank) == 0:
        continue
    gp.showBar(rank, title, axs[row][0], -55)
    row = row + 1


#  -----------------------------------------------

gp.show()




