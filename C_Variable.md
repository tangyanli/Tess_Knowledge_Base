Type|Explain|Scope|Initialization
--|:-----|:--|:--
Internal Variable|在一个函数内部定义<br>也叫做Automatic Variable,函数的参数也属于Internal Variable.<br><br>`int x;`<br>`int y;`<br>`f(double x) {`<br> `double y;`<br>`}`<br>Within the function f, occurrences of x refer to the parameter;Outside of f, they refer to external int x.|整个函数内|缺省情况下，未知.<br>需要用户每次进入function/block时，进行初始化
External Variable|在函数外定义的变量<br>int a = 0;<br>void f(){...}|在整个应用程序范围内都可使用<br>在本文件中：自从该变量定义位置 ~ 文件结尾，都可直接使用该变量<br>在其他文件中：需要先用extern申明后才可使用|缺省情况下，初始化为0.<br>只需要初始化一次，在程序执行之前初始化.
Static External Variable|static修饰External Variable的话，那么该External Variable只可以在本文件可见，其他文件不可见|在本文件中：自从该变量定义位置 ~ 文件结尾 |缺省情况下，初始化为0.<br>只需要初始化一次，在程序执行之前初始化.
Static Internal Variable|Provide private,permant storage with a single function.<br>`/*month_name: return name of n-th month*/`<br>`char *month_name(int n) {`<br><br>`static char *name[] = {`<br>`"Illegal month",`<br>`"Jan","Feb","March"`<br>`"Apr","May","Jun",`<br>`"Jul","Aug","Sep",`<br>`"Oct","Nov","Dec"};`<br><br>`return (n<1 or n>12) ? name[0]:name[n];`<br>`}` |整个函数内|缺省情况下，初始化为0.<br>只需要初始化一次，在程序执行之前初始化.
External Function|默认情况下，所有函数都是External的|整个应用程序都可见并可访问(visible and accessibly).函数使用之前先申明，是为了告诉编译器该函数的类型.
Static Function|本文件可见|本文件
----
---- 
**对于External Variable来说，定义与申明有以下的差异**  
* 定义  
  `int sp;`  
  `double val[MAXVAL]`;
  - Appear outside of any function.
  - Cause storage to be set aside.
  - Also searve as te declaration for the rest of that source file.
* 申明  
  `extern int sp;`  
  `extern double val[]`;
  - Declare for the rest of the source file that sp is an int.
  - Declare val is a double array. (whose size is determined elsewhere. 
