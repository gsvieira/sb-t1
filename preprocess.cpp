#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<regex>
#include"preprocess.h"
#include"tables.h"

//contructor
preProcessor::preProcessor() 
{
    
}

preProcessor::preProcessor(std::string f, std::string filename)
{
    flag = f;
    ofilename = filename;
}

void preProcessor::preProcess(std::fstream& inputfile)//, std::vector<std::string> inputVector)
{
    tables table;
    readfile(inputfile);
    removeRlines();
    if (flag == "-m")
    {
        expandMacro();
    }
    if (flag == "-p")
    {
        analizeIF();
    }
    organizeConst(vec);
    writefile(vec);
    
    
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
void preProcessor::analizeIF()
{
    tables table;
    std::string line;
    std::unordered_map<std::string, std::string> EquTable;
    std::vector<std::string> result, token;
    /* for (auto &&item : vec)
    {
        std::cout<<item<<std::endl;    
    } */
    
    for (auto it = vec.begin(); it != vec.end(); it++) //percorre vector
    {
        if ((*it).find("EQU")!= std::string::npos) //equ encontrado
        {
            std::regex str_expr("\\W+");
            std::string r = std::regex_replace(*it,str_expr," ");
            std::cout << r << std::endl;
            for(int i = 0; i < 3;i++)
            {   

                auto pos = r.find(" ");
                token.push_back(r.substr(0, pos));
                r.erase(0, pos+1);
            }

            for (auto ite = token.begin(); ite != token.end(); ite=ite+3)
            {
                /* auto t= (*ite).substr(0,(*ite).find(":"));
                std::cout << t << " " << *(ite+2)<< std::endl; */
                EquTable[*ite]= *(ite+2);   //coloca os rotulos na equtable 
            }
        }
        if ((*it).find("IF")!= std::string::npos)
        {
            line =  *it;
            size_t position = line.find(" ");
            line = line.substr(position+1);
            if(EquTable.find(line) != EquTable.end()) //achou o rotulo na tabela equ
            {
                //std::cout << EquTable[line] << std::endl;
                if (EquTable[line]  == "1")//avalia
                {
                    //std::cout << *it << std::endl;
                    result.push_back(*(it+1));
                }
                it++;
            } else
            {
                std::cout << "IF com EQU não declarado" << std::endl;
                exit(EXIT_FAILURE);
            }
            
        } 
        /* bool b = !(((*it).find("EQU")!= std::string::npos) || (*it).find("IF")!= std::string::npos);
        std::string str = b ? "1" : "0" ; */
        if (!(((*it).find("EQU")!= std::string::npos) || (*it).find("IF")!= std::string::npos))
        {
        result.push_back(*it);
        }
        

    }
    /* for (auto &&item : EquTable)
    {
        std::cout << "{" << item.first << ": " << item.second << "}\n";
    } */
    vec = result;
}

std::string preProcessor::removeFormat(std::string inputstr)
{
    size_t comentpos;
    std::regex str_expr("\\s+");
    std::string result = std::regex_replace(inputstr,str_expr," ");
    std::regex str_expr1("^[\\s]+|[\\s]+$|;.*");
    result = std::regex_replace(result,str_expr1,"");

    return result;
}



void str_toupper(std::string& s)
{
    std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){ return std::toupper(c);});
}

void preProcessor::organizeConst(std::vector<std::string>& inputVector)
{
    std::vector<std::string> temp, result, debug;
    for(auto line:inputVector)
    {
        if ((line.find("CONST") != std::string::npos) || line.find("SPACE") != std::string::npos) 
        {
            temp.push_back(line);

        }
        else
        {
            result.push_back(line);
        }
    }

    for(auto it = temp.rbegin(); it != temp.rend(); it++)
    {
        result.push_back(*it);
    }
    vec = result;
}
//remove linhas com somente rotulo
void preProcessor::removeRlines()
{
    std::vector<std::string> result;

    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if ((*it).find(":") == (*it).size()-1)
        {
            auto str = *it + *(it+1);
            result.push_back(str);
            it++; 
        }
        else
        {
            result.push_back(*it);
        }
        
    }
    vec = result;
}

void preProcessor::expandMacro()
{
    tables table;
    std::vector<std::string> result;
    bool macroUsed = true;
    bool endmnotfound = true;
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        //std::cout << *it << std::endl;
        if ((*it).find("MACRO")!= std::string::npos) //quando acha uma macro
        {
            macroUsed = false;
            auto pos = (*it).find(":");
            auto index = it;
            auto errorindex = index - vec.begin();
            //try
            table.SymbolTable[(*it).substr(0,pos)] = it-vec.begin();//rotulo da macro adicionado a tabela de simbolos
        
            while (endmnotfound)    //enquanto não acha o final da macro
            {
                if (index == vec.end()) //chegou ao final do arquivo sem achar ENDMACRO
                {
                    std::cout << "Erro na linha " << errorindex << ": Não foi encontrado ENDMACRO";
                    exit(EXIT_FAILURE);
                }
                else if ((*index).find("ENDMACRO")!=std::string::npos) //achou ENDMACRO
                {
                    endmnotfound = false;
                }
                if (!(((*index).find("ENDMACRO")!=std::string::npos) || (*index).find("MACRO")!=std::string::npos))
                {
                table.MacrosTable.push_back(*index);
                }
                index++;
            }
            it = index; //sai no endmacro ou há erro            
        }
        if((*it).find(" ") != std::string::npos)
        {
            size_t macropos = (*it).find(" ");
            std::string rot = (*it).substr(0,macropos);
            if(table.SymbolTable.find(rot) != table.SymbolTable.end()) //se o elemento está na tabela de simbolos
            {
                it++; //ignorar o rotulo da macro que foi chamada
                macroUsed = true;
                for(auto item:table.MacrosTable)
                {
                    result.emplace_back(item); //copia a macro para o vector resultado
                }
            }
        }
        result.emplace_back(*it); //coloca os valores do programa exceto a função de macro no vector resultado
    }
    if(macroUsed == false)
    {
        std::cout<<"Erro: Macro nunca usada" << std::endl;
    }
    /* for (auto &&item : table.MacrosTable)
    {
        std::cout << item << std::endl;       
    } */
    

    vec = result;
}


void preProcessor::writefile(std::vector<std::string> ovec)
{
    std::fstream output;
    output.open(ofilename,std::ios::out);
    for (auto &&line : ovec)
    {
        line += std::string("\n");
        output.write(line.data(), line.size());
    }
    output.close();    
}

void preProcessor::printvec(std::vector<std::string> ovec)
{
    for (auto &&line : ovec)
    {
        std::cout << line << std::endl;
    }
}