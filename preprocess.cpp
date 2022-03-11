#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<regex>
#include"preprocess.h"

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
    readfile(inputfile);
    removeRlines();
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