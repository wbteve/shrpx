shrpx
=====

shrpx是一个基于SPDY(http://www.chromium.org/spdy/)协议的HTTP Proxy server。它的主要用途是让浏览器可以通过它安全的访问网站。

Browser <--> shrpx <--> squid <--> https://www.google.com/

squid虽然是一个很优秀的代理服务器，但是它尚不支持SPDY协议。shrpx就在client和squid之间充当了协议翻译官的作用。

这个项目是从https://github.com/tatsuhiro-t/spdylay 中fork出来的。目前主要的改进是增加了http basic身份认证。下一步的计划是去除squid，直连目标网站。




编译:
(先别尝试，需要openssl 1.0.1及以上版本。）

mkdir b1

cd b1

cmake ..

make

运行:
src/shrpx -f 10.4.1.14:3000 -b 10.4.1.30:80 server.key.insecure server.crt 

-f后面跟的是本机的IP，端口号。
-b后面是后端(即squid）的IP，端口号

最后两个参数是https的私钥key和https的公钥证书。注意证书中的CN一定要与服务器的域名匹配


然后运行Chrome:

C:\Users\cm\AppData\Local\Google\Chrome\Application\chrome.exe --proxy-server=https://10.4.1.14:3000


TODO: 
<p>身份认证</p>
SPDY协议支持4种身份认证模式：Basic, Digest, NTLM and Negotiate (SPNEGO).<br/>
其中Basic和Digest是无状态的。这会导致每个请求多一个Round-trip。于是我下一步的目标是把身份认证方式换成 NTLM 或 SPNEGO。

<p>
关于Basic和Digest认证：<br />
如果客户端发来的header中不含authorization字段。则服务器给客户端返回401或者407的状态码。并在reply header中加上“www-authenticate = Basic”或“www-authenticate = Digest”<br />
如果客户端发来的header中含有authorization字段，则它应该具有“authorization = Basic XXX ”这样的形式。<br />
</p>

downstream: 指向后端的proxy
upstream: 指向browser
