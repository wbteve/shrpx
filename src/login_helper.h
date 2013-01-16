#pragma once

#include <string>

void initPasswd(const std::string& filename);
int do_login(const std::string& username,const std::string& password);