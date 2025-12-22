# 在Ubuntu上运行TLS代理服务器
## 编译nginx
默认情况下，nginx不能和SSLKEYLOGILE一起使用，需要重新编译ngix以及openssl，编译手顺如下
- Download nginx from: https://github.com/nginx/nginx
- Download openssl from: github.com/openssl/openssl
- 编译 & 安装nginx 
```
./auto/configure 
--with-http_ssl_module 
--with-stream_ssl_module 
--with-openssl=/home/tess/Downloads/openssl-openssl
--with-openssl-opt='enable-ssl-trace enable-sslkeylog'

make
#make install
```
## 配置 nginx
修改nginx配置文件如下：监听本ip的443，8000，10443端口，并将捕获的TLS数据解密后再转发到实机172.16.9.116:443端口
```
server {
    listen 443 ssl;
    listen 8000 ssl;
    listen 10443 ssl;
    server_name tess;
    
    # SSL证书配置 - 需要为您的Linux服务器生成或获取证书
    ssl_certificate /etc/cups/ssl/tess-ubuntu.local.crt;
    ssl_certificate_key /etc/cups/ssl/tess-ubuntu.local.key;
    
    # SSL优化配置
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256;
    ssl_prefer_server_ciphers on;
    
    # 转发到打印机
    location / {
        proxy_pass https://172.16.9.116:443;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        
        # 保持连接相关设置
        proxy_http_version 1.1;
        proxy_set_header Connection "";
    }
}

```
## 配置并运行代理TLS服务器
```
#export SSLKEYLOGFILE=/tmp/ssl.key    // 设置密钥文件的存放位置
#/usr/local/ngnix/sbin/ngnix          // 启动TLS代理服务器
```

接着先尝试一下TLS代理服务器是否搭建成功,若如下命令能取得172.16.9.116的能力，那么TLS代理服务器就搭建成功了。
```
ipptool -tv ipps://[Linux-ip-address]:443/ipp/print get-printer-attributes.test
```
## 在Linux截取数据包
通过如下命令在Linux截取数据包
```
# tcpdump -i ens33 host 172.16.3.120 -w capture.pcap
```
