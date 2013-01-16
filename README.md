shrpx
=====

shrpx


编译:

mkdir b1

cd b1

cmake ..

make

运行:
src/shrpx -b 10.4.1.30,80 ~/spdylay/server.key.insecure ~/spdylay/server.crt 

-b后面是后端的地址。IP，端口号

最后两个参数是https的私钥key和https的公钥证书。注意证书中的CN一定要与服务器的域名匹配


然后运行Chrome:

C:\Users\cm\AppData\Local\Google\Chrome\Application\chrome.exe --proxy-server=https://10.4.1.14:3000


TODO: 
<p>身份认证</p>
SPDY协议支持4种身份认证模式：Basic, Digest, NTLM and Negotiate (SPNEGO).<br/>
其中Basic和Digest是无状态的。

<p>
关于Basic和Digest认证：<br />
如果客户端发来的header中不含authorization字段。则服务器给客户端返回401或者407的状态码。并在reply header中加上“www-authenticate = Basic”或“www-authenticate = Digest”<br />
如果客户端发来的header中含有authorization字段，则它应该具有“authorization = Basic XXX ”这样的形式。<br />
</p>
