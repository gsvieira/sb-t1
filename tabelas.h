#pragma once

#include"tabelas.h"
#include<unordered_map>
#include<string>

struct ti
{
    std::string opcode, size, opcount;
    ti(std::string a, std::string b, std::string c);
};


struct ts
{
    std::string symbol, value;
};

struct td
{
    std::string size, opcount;
};



