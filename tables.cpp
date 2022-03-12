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

tables::tables()
{
}

equ::equ(std::string a, bool b)
{
symbol = a;
used = b;
}
/* auto tables::addequ(std::string a,std::string b, bool c)
{
    this->EquTable[a] = equ(b,c);
} */
