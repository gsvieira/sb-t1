#pragma once

class preProcessor
{
    std::vector<std::string> vec;
    //acrescentar tabelas de instruções, tabela de simbolos, tabela de diretivas 

    std::string removeFormat(std::string);
    public:
    preProcessor();
    void readfile(std::fstream&);
    int preProcess(std::vector<std::string>);
};

void str_toupper(std::string& s);

