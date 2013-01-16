shrpx
=====

shrpx


编译:

mkdir b1

cd b1

cmake ..

make

运行:
src/shrpx -b 10.4.1.30,80 -s ~/spdylay/server.key.insecure ~/spdylay/server.crt 

-b后面是后端的地址。IP，端口号

最后两个参数是https的私钥key和https的公钥证书。注意证书中的CN一定要与服务器的域名匹配


然后运行Chrome:

C:\Users\cm\AppData\Local\Google\Chrome\Application\chrome.exe --proxy-server=https://10.4.1.14:3000

