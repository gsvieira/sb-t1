#include"tables.h"


instruction::instruction()
{
}
instruction::instruction(std::string i, std::string j, std::string k)
{
    opcode = i;
    size = j;
    opcount = k;
}

instruction::~instruction()
{
}

tables::tables();
{
}