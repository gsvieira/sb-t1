#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<string>
int main(int argc, char* argv[])
{
std::fstream file (argv[3]);


if (file.is_open())
{
    if (!strcmp(argv[2],"-m")||!strcmp(argv[2],"-p")||!strcmp(argv[2],"-o"))
    {
        std::cout << "flag invalida!"<< std::endl;
    }
    


    
}





}