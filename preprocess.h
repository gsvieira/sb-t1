#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<regex>
#include"preprocess.h"



class preProcessor
{
    std::vector<std::string> vec;
    std::string flag, ofilename;
    

    std::string removeFormat(std::string);
    void printvec(std::vector<std::string>);
    void removeRlines();
    void expandMacro();
    void analizeIF();
    public:
    preProcessor();
    preProcessor(std::string, std::string);
    void readfile(std::fstream&);
    void preProcess(std::fstream&);
    void organizeConst(std::vector<std::string>&);
    void writefile(std::vector<std::string>);
};

void str_toupper(std::string& s);

