#pragma once

class preProcessor
{
    std::vector<std::string> vec;
    std::string ofilename;
    //acrescentar tabelas de instruções, tabela de simbolos, tabela de diretivas 

    std::string removeFormat(std::string);
    void printvec(std::vector<std::string>);
    void removeRlines();
    void expandMacro();
    public:
    preProcessor();
    preProcessor(std::string);
    void readfile(std::fstream&);
    void preProcess(std::fstream&);//, std::vector<std::string>);
    void organizeConst(std::vector<std::string>&);
    void writefile(std::vector<std::string>);
};

void str_toupper(std::string& s);

