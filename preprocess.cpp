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

preProcessor::preProcessor(std::string filename)
{
    ofilename = filename;
}

void preProcessor::preProcess(std::fstream& inputfile)//, std::vector<std::string> inputVector)
{
    tables table;
    readfile(inputfile);
    removeRlines();
    organizeConst(vec);
    writefile(vec);
    if (flag == "-m")
    {
        expandMacro();
    }
    
}

void preProcessor::readfile(std::fstream& inputfile)
{
    std::string line;
    while (!inputfile.eof())
    {
        getline(inputfile, line);
        str_toupper(line);
        removeFormat(line);
        vec.emplace_back(line);
    }
    //std::cout << vec[0] <<std::endl;

}

std::string preProcessor::removeFormat(std::string inputstr)
{
    size_t comentpos;
    std::regex str_expr("\\s+");
    std::string result = std::regex_replace(inputstr,str_expr," ");
    std::regex str_expr1("^[\\s]+|[\\s]+$");
    result = std::regex_replace(result,str_expr1,"");
    comentpos = result.find(";");
    //remove comment
    if (comentpos != std::string::npos)
    {
        result = result.substr(0, comentpos);
    }
    //std::cout << result <<std::endl;

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
    bool endmnotfound = true;
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if ((*it).find("MACRO")!= std::string::npos)
        {
            auto index = it;
            auto errorindex = index - vec.end();
            //TODO: acrecentar na tabela de simbolos

        
            while (endmnotfound)
            {
                if (index != vec.end())
                {
                    std::cout << "Erro na linha " << errorindex << ": Não foi encontrado ENDMACRO";
                }
                else if ((*index).find("ENDMACRO")!=std::string::npos)
                {
                    endmnotfound = false;
                }
                table.MacrosTable.puch_back(*index);
                


                index++;
            }
            
            
        }
        
    }
    
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