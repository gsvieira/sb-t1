#include"process.h"


process::process(/* args */)
{
}

process::~process()
{
}


process::firstpass(std::fstream& inputfile, std::unordered_map<std::string, instruction> Itable)
{
    int line_count = 1, position_count = 0;
    std::string line;
    while (!inputfile.eof())
    {
        getline(inputfile, line);
        if (line.find(":")!= std::string::npos)
        {   

            size_t rotulo_pos = line.find(":");
            std::string rotulo = line.substr(0,rotulo_pos);
            line.erase(0, rotulo_pos+1);
            vec.push_back(rotulo);
            while (!line.empty())
            {
            auto pos = line.find(" ");
            vec.push_back(line.substr(0, pos));
            line.erase(0, pos);
            }
            
            if(table.SymbolTable.find(rotulo) != table.SymbolTable.end()) //se o elemento está na tabela de simbolos
            {
                std::cout << "ERRO: – declarações ou rótulos repetidos" << std::endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                table.SymbolTable[rotulo] = std::to_string(position_count);
            }

        }


        vec.emplace_back(line);
    }

}

void preProcessor::readfile(std::fstream& inputfile)
{
    std::string line;
    while (!inputfile.eof())
    {
        getline(inputfile, line);
        str_toupper(line);
        line = removeFormat(line);
        vec.emplace_back(line);
    }
    //std::cout << vec[0] <<std::endl;

}