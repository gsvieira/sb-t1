#include"process.h"


process::process(/* args */)
{
}

process::~process()
{
}


void process::firstpass(std::fstream& inputfile, std::unordered_map<std::string, instruction>& Itable)
{
    int line_count = 1, position_count = 0;
    std::string line, operacao;
    int operand_count = 0;
    while (!inputfile.eof())
    {
        getline(inputfile, line);
        if (line.find(":")!= std::string::npos)
        {   

            size_t rotulo_pos = line.find(":");
            std::string rotulo = line.substr(0,rotulo_pos);
            line.erase(0, rotulo_pos+1);
            
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

        auto pos = line.find(" ");
        operacao = line.substr(0, pos);

        while (!line.empty())
        {
        auto pos = line.find(" ");
        vec.push_back(line.substr(0, pos));
        line.erase(0, pos);
        operand_count++;
        }

        if (Itable.find(operacao) != Itable.end())
        {
            position_count +=  stoi(Itable[operacao].size);
        }
        else
        {
            if (operacao.find("SPACE") != std::string::npos)
            {
                position_count++;
            }
            else if (operacao.find("CONST") != std::string::npos)
            {
                position_count++;
            }
            else
            {
                std::cout << "operação desconhecida" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout<< position_count<<std::endl;
    }

}

void process::secondpass(std::fstream& inputfile, std::unordered_map<std::string, instruction>& Itable)
{

}