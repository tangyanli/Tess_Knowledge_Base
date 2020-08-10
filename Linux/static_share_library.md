||静态库|动态库|
|:--|:--|:--|
|生成|# gcc -c hello.c<br># ar cr libmyhello.a hello.o|# gcc –fPIC -c hello.c<br># gcc -shared -o libmyhello.so hello.o|
|使用|#gcc -o hello main.c -L. -lmyhello|#gcc -o hello main.c -L. -lmyhello|
|顺序|1.	ld会去找GCC命令中的参数-L<br>2.	再找GCC 的环境变量LIBRARY_PATH<br>3.	找目录/lib /usr/lib /usr/local/lib|链接顺序<br>1.	–rpath<br>2.	–rpath-link指定第二层链接库的位置<br>3.	GCC命令中的参数-L<br>4.	Gcc的环境变量：LIBRARY_PATH<br>5.	/lib, /usr/lib, /usr/local/lib这些是gcc写在程序里的。<br><br>运行时加载顺序：<br>(1). –rpath<br>(2). 环境变量LD_LIBRARY_PATH指定的动态搜索路径, 通过如下导入：export LD_LIBRARY_PATH=/home/tess<br>(3) 配置文件/etc/ld.so.conf中指定的动态搜索路径<br>(4) /lib, /usr/lib, /usr/local/lib|