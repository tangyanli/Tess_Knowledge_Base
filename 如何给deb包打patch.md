# 1.从源中取得代码以及需要的依赖库
* sudo apt-cache showsrc xxx		    &nbsp;&nbsp;&nbsp;&nbsp;*//查询是否有该source*
* sudo apt-get source xxx				    &nbsp;&nbsp;&nbsp;&nbsp;*//获得source*
* sudo apt-get build-dep xxx		    &nbsp;&nbsp;&nbsp;&nbsp;*//获得source需要的依赖库*

# 2.打上patch文件
* cd xxx
* quilt import sample.patch
* quilt push
* quilt refresh

# 3.修改 changelog文件
* dch -n "Apply sample.patch"					&nbsp;&nbsp;&nbsp;&nbsp;*//dch工具在devscript包中*

# 4.编译
* sudo dpkg-buildpackage
