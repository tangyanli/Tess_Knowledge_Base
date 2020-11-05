REF

+ https://www.debian.org/doc/manuals/debmake-doc/index.en.html<br>
+ https://www.debian.org/doc/manuals/maint-guide/index.en.html<br>

# 1. 如何制作简易的debian包
## 1.1. 创建如下文件夹结构
```
DEBIAN
|--conffiles
|--control
|--md5sums
etc
usr
```
## 1.2. 在mips上编译好二进制文件
## 1.3. 将二进制文件拷贝到etc/usr下面
```
md5sum file
dpkg-deb -b example-package
```

# 2. 如何在Ubuntu 14.04上编译MIPS版本的airscan
## 2.1. 安装必要的package
```
sudo apt install build-essential
```

## 2.2. 下载代码并解压
```
tar -zxvf sane-airscan-099.19.tar.gz
```
解压后目录如下:
```
sane-airscan-0.99.19
sane-airscan-0.99.19.tar.gz
```
## 2.3. 生成orig.tar.gz文件
```
cd sane-airscan0.99.19
dh_make -f ../sane-airscan-0.99.19.tar.gz
```
运行这一步后目录如下:
```
sane-airscan-0.99.19
|----debian
sane-airscan-0.99.19.orig.tar.gz
sane-airscan.tar.gz
```
注意：若一不小心把debian下的模板玩坏了，可以使用`dh_make --addmissing`参数来还原

## 2.4. 编译debian文件夹下的文件
### 2.4.1. control文件
需要维护build-dep信息，可以用命令`$objdump -p libsane-airscan.so | grep NEEDED`来查看需要哪些依赖库

### 2.4.2. copyright
### 2.4.3. changelog
若打了patch的话，建议修改一下`dch -n "Apply test.patch"`

## 2.5. 打上patch
建议和Debian10上的规则一样，把patch文件拷贝到`./debian/patches`文件夹下面。<br>
打上patch `$patch -p1 < ./debian/patches/test.patch`

## 2.6. 编译
* sudo dpkg-buildpackage -us -uc

# 3. 如何在Debian10上编译MIPS版本的airscan
## 3.1. 从源中取得代码以及需要的依赖库
```
sudo apt-cache showsrc xxx		//查询是否有该source
sudo apt-get source xxx			//获得source
sudo apt-get build-dep xxx		//获得source需要的依赖库
```

## 3.2. 打上patch文件
```
cd xxx
quilt import sample.patch
quilt push
quilt refresh
```

## 3.3. 修改 changelog文件
```
dch -n "Apply sample.patch"	 //dch工具在devscript包中
```

## 3.4. 编译
* sudo dpkg-buildpackage -us -uc
