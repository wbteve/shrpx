shrpx
=====

shrpx是一个基于SPDY( http://www.chromium.org/spdy/ )协议的HTTP forward Proxy server。它的主要用途是让浏览器可以通过它安全的访问网站。

Browser <--> shrpx <--> 目标网站(如https://www.google.com/)


编译:
编译前需要：
gcc >= 4.4、g++ >= 4.4、cmake >= 2.8、openssl >= 1.0.1、libevent2（含ssl） >= 2.0.8 、zlib >=1.2.3

mkdir b1

cd b1

cmake ..

make

配置文件示例：

private-key-file=/home/app/shrpx/private.key #https证书私钥。 <br />
certificate-file=/home/app/shrpx/mycert.pem  #https证书公钥。注意证书中的CN一定要与服务器的域名匹配 <br />
frontend=10.4.1.14:3000 #本机的IP，端口号。 <br />
user-passwd-file=proxy_pass.txt #密码文件 <br />

运行:
./shrpx -c shrpx.ini -D

然后运行Chrome:

C:\Users\cm\AppData\Local\Google\Chrome\Application\chrome.exe --proxy-server=https://10.4.1.14:3000

注意，上述命令的末尾不要多一个"/"字符！！！是“https://10.4.1.14:3000”而不是“https://10.4.1.14:3000/”

TODO: 
downstream: 指向后端的proxy。 需要支持两种downstream，http和socket。目前只支持http。所以https网站无法访问。
upstream: 指向browser

欢迎发邮件给我 me@sunchangming.com

Blog: https://www.sunchangming.com/blog/

这个项目是从https://github.com/tatsuhiro-t/spdylay 中fork出来的。

