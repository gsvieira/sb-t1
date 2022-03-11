#include"tabelas.h"
#include<unordered_map>

ti::ti(std::string a, std::string b, std::string c)
{
  opcode = a;
  size = b;
  opcount = c;
}

std::unordered_map<int,char> map1;
std::unordered_map<int, char>::iterator cursor;
map1[1] = 'a';
map1[2] = 'b';
cout << map1.bucket_count() << endl;




/* std::unordered_map<std::string, ti> tabelaI;
std::unordered_map<std::string, ts> tabelaS;
std::unordered_map<std::string, td> tabelaD;
std::string const temp = "ADD";
tabelaI[temp] = ("01","2","1")  //std::insert(std::makepair("ADD", ("01","2","1")) 

{"SUB", ("02","2","1")}, 
{"MUL", ("03","2","1")},
{"DIV", ("04","2","1")},
{"JMP", ("05","2","1")},
{"JMPN", ("06","2","1")},
{"JMPP", ("07","2","1")},
{"JMPZ", ("08","2","1")},
{"COPY", ("09","3","2")},
{"LOAD", ("10","2","1")},
{"STORE", ("11","2","1")},
{"INPUT", ("12","2","1")},
{"OUTPUT", ("13","2","1")},
{"STOP", ("14","1","0")}); */