#!/bin/bash

# 内部统计总 CPU 消耗
# grep CPU A_2023-05-08_00-00.log |awk '{print $2, $7}'|awk -F"[:.,]" '{print $1*3600+$2*60+$3, $5}' > temp.log

# 内部统计 delay 变化
grep "\[STATUS]" A_2023-05-11_00-00.log |awk '{print $6, $8, $9, $12, $13, $14}'| awk -F"," '{print $1, $3, $5, $7, $9, $11}'
thread_name max_delay nmsg logic_ms parse_ms gc_ms

# 内部统计消息数量变化
grep "\[CPU]" A_2023-05-11_00-00.log| awk '{for(i=8;i<=12;i++)printf("%s",$i); print ""}'|awk -F"," '{print $2,$4,$6,$8,$11}'
Pkg 每秒添加进消息队列总消息数量
Db  每秒收到的db消息数量
Tm  每秒添加的定时器数量
nBuf 当前存在的 buf 数
Recv 每秒接收的网络消息数量

# 内部统计消息耗时情况
grep "\[CMD]" B_2023-07-14_00-00.log| grep total_ms| awk '{print $6, $7, $9, $10}'| awk -F"," '{print $1, $2, $4, $6}'
thread_name rpc_name use_ms total_ms

#------------------------------------------------
# 外部統計 CPU 消耗
# pidstat -p 10201 -ut 1 > temp.log

# 外部统计详细 cpu 消耗
# grep -v UID temp.log| grep AM| awk '{print $9, $11}'| sed 's/|__/sub/g' > temp2.log

# 外部统计详细 cpu 平均消耗 (为了使用 -l 选项让所有输出到一行，该选项会省略掉平均值输出，所以平均值需要改为自己计算)
# grep -v UID temp.log| grep Average| awk '{print $8, $10}'| sed 's/|__/sub/g' > temp3.log
#------------------------------------------------

# -p 进程id -u CPU信息 -d IO信息 -r 内存缺页和内存消耗 -t 显示线程信息 -h 将几个选项的内容合并到一起显示 1 采样间隔时间 1 秒 [采样次数不传默认为 1 次]
# nohup pidstat -p 10201 -udrth 1 > temp.log 2>/dev/null &

# 输出内容为
#      Time   UID      TGID       TID    %usr %system  %guest    %CPU   CPU  minflt/s  majflt/s     VSZ    RSS   %MEM   kB_rd/s   kB_wr/s kB_ccwr/s  Command
1683555986     0     10201         0   97.00    1.00    0.00   98.00     3     47.00      0.00 3851748 2983896  37.26      0.00      0.00      0.00  game
1683555986     0         0     10201    0.00    0.00    0.00    0.00     3      0.00      0.00 3851748 2983896  37.26      0.00      0.00      0.00  |__game
1683555986     0         0     10205    0.00    0.00    0.00    0.00     2      0.00      0.00 3851748 2983896  37.26      0.00      0.00      0.00  |__log_f

# 外部统计详细 cpu 消耗
# grep -v "UID\|pidstat" temp.log| grep 0| awk '{print $8, $10, $13, $15, $16, $18}'| sed 's/|__/sub/g' > temp2.log
# cpu_use flt rss ior iow thread_name
