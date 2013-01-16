#include <iostream>
#include <stdexcept>
#include <map>
#include <string.h>
#include <algorithm>

static std::map<std::string,std::string> userinfo;

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}


void initPasswd(const std::string& filename){
	FILE* file=fopen(filename.c_str(),"r");
	if(file==NULL)
	  throw std::runtime_error("open password file fail");
	char buf[4096];
	buf[4095]='\0';
	while(fgets(buf,sizeof(buf)-1,file)!=NULL){
		if(strlen(buf)==0)
		   continue;
		char* p=strchr(buf,'=');
		if(p==NULL)
			throw std::runtime_error("password file format error");
		std::string pass(p+1);
		rtrim(pass);
		userinfo[std::string(buf,p-buf)]=pass;
	}
	fclose(file);
}

int do_login(const std::string& username,const std::string& password){
    //TODO:身份认证
    //std::cerr<<"username="<<username<<",password="<<password;
	auto iter=userinfo.find(username);
	if(iter==userinfo.end()) return 0;
	if(iter->second != password) return 0;
	return 1;
}