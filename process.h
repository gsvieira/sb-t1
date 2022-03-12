#pragma once
#include"preprocess.h"
#include"tables.h"



class process
{
private:
    std::vector<std::string> vec;
    std::string flag, ofilename;
    tables table;
public:
    void firstpass(std::fstream&, std::unordered_map<std::string, instruction>);
    void readfile(std::fstream&);
    process(/* args */);
    ~process();
};

