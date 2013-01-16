shrpx
=====

shrpx是一个基于SPDY( http://www.chromium.org/spdy/ )协议的HTTP Proxy server。它的主要用途是让浏览器可以通过它安全的访问网站。

Browser <--> shrpx <--> squid <--> 目标网站。如https://www.google.com/

squid虽然是一个很优秀的代理服务器，但是它尚不支持SPDY协议。shrpx就在client和squid之间充当了协议翻译官的作用。

这个项目是从https://github.com/tatsuhiro-t/spdylay 中fork出来的。目前主要的改进是增加了http basic身份认证。下一步的计划是去除squid，直连目标网站。




编译:
编译前需要：
gcc >= 4.4、g++ >= 4.4、cmake >= 2.8、openssl >= 1.0.1、libevent2（含ssl） >= 2.0.8 、zlib >=1.2.3

mkdir b1

cd b1

cmake ..

make

配置文件示例：
backend=127.0.0.1:3128 #后端(即squid）的IP，端口号
private-key-file=/home/app/shrpx/private.key #https证书私钥。
certificate-file=/home/app/shrpx/mycert.pem  #https证书公钥。注意证书中的CN一定要与服务器的域名匹配
frontend=10.4.1.14:3000 #本机的IP，端口号。
add-x-forwarded-for=yes #转发给squid的时候加上x-forward-for


运行:
./shrpx  --conf shrpx.ini -D

然后运行Chrome:

C:\Users\cm\AppData\Local\Google\Chrome\Application\chrome.exe --proxy-server=https://10.4.1.14:3000


TODO: 
计划是去除squid，直连目标网站。

downstream: 指向后端的proxy。 目前支持两种downstream，http和spdy。 https肿么办？
upstream: 指向browser
