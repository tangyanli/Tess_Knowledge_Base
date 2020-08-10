Sample

Client <br>
客户端发送一个HTTP request请求到服务器的消息包括以下格式：请求行，请求头部，空行和请求数据<br>
`GET /hello.txt HTTP/1.1`<br>
`User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3`<br>
`Host: www.example.com`<br>
`Accept-Language: en, mi`<br>

根据HTTP标准，HTTP请求可以使用多种请求方法<br>
- GET: 请求指定的页面信息，并返回实体主体。 <br>
- HEAD: 类似于 GET 请求，只不过返回的响应中没有具体的内容，用于获取报头。<br>
- POST: 向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST 请求可能会导致新的资源的建立和/或已有资源的修改。<br>
- PUT: 从客户端向服务器传送的数据取代指定的文档的内容。<br>
- DELETE: 请求服务器删除指定的页面。<br>
- CONNECT: HTTP/1.1 协议中预留给能够将连接改为管道方式的代理服务器。<br>
- OPTIONS: 允许客户端查看服务器的性能。<br>
- TRACE: 回显服务器收到的请求，主要用于测试或诊断。<br>
- PATCH: 是对 PUT 方法的补充，用来对已知资源进行局部更新 。<br>

Server <br>
HTTP Response也由四个部分组成，状态行，消息报头，空行和相应正文<br>
`HTTP/1.1 200 OK`<br>
`Date: Mon, 27 Jul 2009 12:28:53 GMT`<br>
`Server: Apache`<br>
`Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT`<br>
`ETag: "34aa387-d-1568eb00"`<br>
`Accept-Ranges: bytes`<br>
`Content-Length: 51`<br>
`Vary: Accept-Encoding`<br>
`Content-Type: text/plain`<br>

HTTP Response头信息<br>
- Allow: 服务器支持哪些请求方法（如GET、POST等）。<br>
- Conetent-Encoding: 文档的编码（Encode）方法。<br>
- Content-Type: 表示后面的文档属于什么MIME类型。Servlet默认为text/plain，但通常需要显式地指定为text/html。由于经常要设置Content-Type，因此HttpServletResponse提供了一个专用的方法setContentType。<br>
- Data: 当前的GMT时间。<br>
- Location: 表示客户应当到哪里去提取文档, Location通常不是直接设置的，而是通过HttpServletResponse的sendRedirect方法，该方法同时设置状态代码为302。<br>
- Server: 服务器名字。<br>
- Refresh: 表示浏览器应该在多少时间之后刷新文档，以秒计。<br>
- connection: request和response header中都有可能出现一个connection的头，此header的含义是当client和server通信时对于长链接如何进行处理。

HTTP状态码<br>
当浏览者访问一个网页时，浏览者的浏览器会向网页所在服务器发出请求。当浏览器接收并显示网页前，此网页所在的服务器会返回一个包含HTTP状态码的信息头（server header）用以响应浏览器的请求。

HTTP状态码的英文为HTTP Status Code。<br>
下面是常见的HTTP状态码：<br>
200 - 请求成功 <br>
301 - 资源（网页等）被永久转移到其它URL<br>
404 - 请求的资源（网页等）不存在<br>
500 - 内部服务器错误<br>

HTTP content-type<br>
Content-Type（内容类型），一般是指网页中存在的 Content-Type，用于定义网络文件的类型和网页的编码，决定浏览器将以什么形式、什么编码读取这个文件，这就是经常看到一些 PHP 网页点击的结果却是下载一个文件或一张图片的原因。
Content-Type 标头告诉客户端实际返回的内容的内容类型。

`Content-Type: text/plain`<br>
- text/html ： HTML格式
- image/gif ：gif图片格式
- application/xhtml+xml ：XHTML格式
- application/json： JSON数据格式
- application/pdf：pdf格式
- application/octet-stream ： 二进制流数据（如常见的文件下载）
- application/ipp: IPP协议
