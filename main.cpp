#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<string>
#include"preprocess.h"

int main(int argc, char* argv[])
{
    if (argc <= 3 || argc > 4)
    {
        std::cout << "Forma de utilizar o programa incorreta!" << std::endl << "Exemplo: ./montador -p myprogram.asm saida.obj";
    }
    
    std::fstream file(argv[2]);
    preProcessor unprocessed(argv[3]);
    

    if (file.is_open())
    {
        if (!strcmp(argv[1], "-p"))
        {
            std::cout << "-p"<< std::endl;
        
        }else if (!strcmp(argv[1], "-m"))
        {
            std::cout << "-m"<< std::endl;
            unprocessed.preProcess(file);
        }
        else if (!strcmp(argv[1], "-o"))
        {
            std::cout << "-o"<< std::endl;
        }
        else
        {
            std::cout << "flag invalida!"<< std::endl;
        }
        
    }
    else
    {
        std::cout << "Não foi possivel abrir o arquivo" << std::endl;
    }


}