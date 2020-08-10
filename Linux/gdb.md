# 1. 相关的设置命令
|命令|备注|
|:--|:--|
| # ulimit -c <br> 0 <br> # ulimit -c unlimted | ulimit -c shows the maximum size of core dumps created.<br>0: disabling core dumps<br>|
|# cat /proc/sys/kernel/core_pattern <br>core|这意味着转存 core dump 时，Linux 会将进程内存空间转存到当前目录下的 core 文件当中|
|# echo “/var/cores/core.%e.%p” > /proc/sys/kernel/core_pattern| 将core存在某个全局目录中 %h表示机器名称，%t表示转存时间。|

# 2. 基本命令
|命令|备注|
|:--|:--|
|gdb main|	进入调试|
|(1)	run 命令行参数 <br>(2)	set args命令行函数	输入命令行参数 (eg.)|run www.baidu.com<br>set args www.baidu.com|
|start / r	| 开始调试 |
|next / n	| 单步进入下一条 = F10 |
|step / s	|单步进入函数=F11 |
|si	| 一条指令一条指令的单步调试 |
|continue / c	| 连续运行到断点停下来 |
|Disassemble	| 反汇编当前的函数或者指定的函数 |
|disas/s	| 安装了调试信息包后，gdb可以将源代码和汇编代码都列出来 |
| backtrace / bt | 可以查看函数调用的栈桢 <br> 例如:<br> #0 add_range (low =1, high=100) at main.c : 6<br> #1 0x0005555555 int main() at main.c:14<br>|
| Frame 数字	| 察看每一个栈桢 <br>例如 frame 0 // 察看main.c第6行的代码 |
|“layout” or “layout src”	| 显示代码 |
|layout split | 在独立窗口同步显示源代码的汇编代码。 |
| gdb –tui simple-scan	| gdb 的文本用户界面 TUI (Text User Interface) |
| dir 文件夹名称 | 若找不到文件,可以明确指定路径 |
| list / l	| 列出源代码,接着上次的位置往下列,每次列10行 |
| list 行号	| 列出从第几行开始的源代码 |
|list 函数名	| 列出某个函数的源代码|
| info / f 栈桢数目	| i 1 <br>对于以上情况,可以f 1进入main()函数,<br>然后再通过i locals来参看局部变量的值|
| info / i locals	| 察看函数局部变量的值 |
| info /i breakpoints	| 察看已经设置的断点 |
| info watchpoints	| 打印一个列表,包含了watchpoints, breakpoints, and catchpoints.|
| info inferiors |	察看进程信息. <br>例如: <br> Num Description<br>*2 process 19420<br> 1 process 19397|
| info registers	| 察看寄存器信息 |
| info threads	| 察看线程信息. <br>3 Thread 0xb7fe4b90 (LWP 19463) 0x0011040402 in _..() <br>2 Thread 0xb7fe56c0 (LWP 19458) processB () at main.c 58<br>*1 Thread 0xb7fe56c0 (LWP 19455) processA () at main.c:31|
| info/i proc m	| Info proc mapping, 查看内存映射状态 |
| delete inf 数字 |	用编号删除某个断点 |
| delete breakpoints	| 删除所有的断点 |
| disable breakpoints 数字	| 使得某个断点无效 |
| print / p 变量名 | |
| print / p 表达式	| 察看变量的值<br>修改变量的值,比如 p result[2]=33<br>set print element 0命令显示完整的字符串 |
| p $esp	| 打印寄存器esp的值 |
| finish | 	让程序一直运行到从当前函数返回为止 |
| ret	| 跳过函数执行立即返回 |
|set var sum=0	| 给local变量赋值 |
| set $rdi=0xbecb90	| set 命令复写内存 |
| display 变量	| 每次停下来都显示当前变量的值,然后继续往下走 |
| undisplay 变量	| 取消对变量的跟踪 |
| break / b行号	| 设置断点 |
| break / b 行号 if sum != 0 |	仅仅当sum不等于0时才中断<br>然后用 run (r)重新从程序开头连续执行 |
| break 函数名	|
| cond 1 $rdi==0x0	| 将断点1改为条件断点，让它只在%rdi寄存器是0的时候才被触发。|
| x/7b input	| 从某个位置开始打印存储器的一段内容,全部当成字节来看,而不区分哪些字节属于哪些变量|	
| set print pretty on	| 显示自定义结构体 |
| 直接回车	| 用适当的参数重复上一条命令 |
	
# 3. 调试多线程,多进程
|命令|备注|
|:--|:--|
| set detach-on-fork <mode>	| Tells gdb whether to detach one of the processes after a fork, or retian debugger control over the both<br>[on]<br>The child process (or parent process, depending on the value of follow-fork-mode) will be detached and allow running independently, This is the default.<br>[off]<br>Both processes will be held under the control of GDB. One process (child or parent, depending on the value of follow-fork-mode) is debugged as usual, while the other is held suspended.<br>例子:<br>Step1调试主进程,block子进程<br>set detach-on-fork off<br>catch fork<br>Step2 切换到子进程<br>inferior 2<br>|
| set follow-fork-mode <mode> | [parent]<br>The origianl process is debugged after a fork.<br>The child process runs unimpeded.This is the default.<br>[child]The new process is debugged after a fork. The parent process runs unimpeded.
| catch <event>	| Stop when event occus.event can be any of the following: [throw]<br>[catch]<br>[exception]<br>[exception unhandled]<br>[assert]<br>[exec] : A call to exec. <br>[fork] : A call to fork. <br>[vfork]: A call to vfork.<br>[load]<br>[load libname]<br>[unload]<br>[unload libname]|

# 4. Attach 进程调试
|命令|备注|
|:--|:--|
|gdb |	运行gdb|
|(gdb) attach process id	||
|(gdb) stop | 暂停进程,设置一些断点和一些watch |
| (gdb) break 37|	|
| (gdb) continue / s / n	||








