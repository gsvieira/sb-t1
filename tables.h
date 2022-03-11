#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>

struct instruction
{
    std::string opcode, size, opcount;
    
    instruction();
    instruction(std::string, std::string, std::string);
    ~instruction();
    
};

class tables
{
private:

public:
    std::unordered_map<std::string, std::string> SymbolTable
    std::vector<std::string> MacrosTable;
    tables();
};









void readItablefromfile(std::string, std::unordered_map<std::string, instruction>&);
