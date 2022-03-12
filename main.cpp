#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<string>
#include"preprocess.h"
#include"tables.h"
#include"process.h"

int main(int argc, char* argv[])
{
    if (argc <= 3 || argc > 4)
    {
        std::cout << "Forma de utilizar o programa incorreta!" << std::endl << "Exemplo: ./montador -p myprogram.asm saida.obj";
    }
    
    std::fstream file(argv[2]);
    preProcessor unprocessed(argv[1], argv[3]);
    std::unordered_map<std::string, instruction> Itable;
    std::vector<std::string> MDT;
    readItablefromfile("tabelaintrucao.txt", Itable);
    process preprocessed;

    
    // std::cout << b.opcode << std::endl;

    if (file.is_open())
    {
        if (!strcmp(argv[1], "-m")||!strcmp(argv[1], "-p"))
        {
            unprocessed.preProcess(file);
        }
        else if (!strcmp(argv[1], "-o"))
        {
            std::cout << "-o"<< std::endl;
            preprocessed.firstpass(file, Itable);
        }
        else
        {
            std::cout << "flag invalida!"<< std::endl;
        }
        
    } else
    {
        std::cout << "Não foi possivel abrir o arquivo" << std::endl;
    }


}

void readItablefromfile(std::string ifilename, std::unordered_map<std::string, instruction>& table)
{
    std::fstream ifile(ifilename);
    std::string line;
    std::vector<std::string> token;
    size_t pos;

    if (ifile.is_open())
    {
        while (!ifile.eof())
        {
            getline(ifile, line);
            for(int i = 0; i < 4;i++)
            {
            pos = line.find(",");
            token.push_back(line.substr(0, pos));
            line.erase(0, pos+1);
            }
            //std::cout << token[0] << token[1] << token[2] << token[3] << std::endl;
            //std::cout << (*it).data()<< std::endl;
            for (auto it = token.begin(); it != token.end(); it=it+4)
            {
            table[*it]=instruction(*(it+1), *(it+2), *(it+3));    
            }
            
            
        }
        
        
    }
    else
    {
        std::cout << "tabelainstruções.txt não pode ser aberto" << std::endl;
    }

}




void process ()
{

}