(1) 在/home/tess/helloworld下创建文件夹<br>
mkdir -p /home/tess/helloworld /{RPMS,SRPMS,BUILD,SOURCES,SPECS}

(2) 创建源文件并创建tarball，并把tarball放在/home/tess/helloword/SOURCES下<br>
hello.c:<br>
`#include <stdio.h> `<br>
`int main() `<br>
`{ `<br>
`	printf("Hello, World!\n"); return 0; `<br>
`}`<br>
`$mkdir -p hello-0.1 `<br>
`$mv hello.c hello-0.1`<br>
`$tar czvf hello-0.1.tar.gz hello-0.1 `<br>
`$mv hello-0.1.tar.gz /home/tess/helloworld/SOURCES/`<br>

(3) 创建SPEC文件<br>
`Name: hello`<br>
`Version: 0.1`<br>
`Release: 1`<br>
`Source: hello-0.1.tar.gz`<br>
`License: GPL`<br>
`Group: Application`<br>
`BuildRoot: %{_topdir}/root/`<br><br>

`%description`<br>
`This is a software for making you life more beautiful!`<br><br>

`%prep`<br>
`%setup -q`<br><br>

`%build`<br>
`gcc -o hello hello.c`<br><br>

`%install`<br>
`pwd`<br>
`rm -rf %{buildroot}`<br>
`mkdir -p %{buildroot}/usr/local/bin`<br>
`cp hello %{buildroot}/usr/local/bin/hello`<br><br>

`%files`<br>
`/usr/local/bin/hello`<br>
   
(4)编译RPM 
$rpmbuild –define “_topdir /home/tess/helloworld” –vv –ba helloworld/SPECS/hello.spec

(5) 安装并查看编译好的RPM<br>
  $rpm –ivh hello-0.1-1.x86_64<br>
  $rpm –qi hello-0.1-1.x86_64<br>
