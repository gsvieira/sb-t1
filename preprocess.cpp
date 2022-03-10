#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<regex>
#include"preprocess.h"

preProcessor::preProcessor()
{
    
};

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
std::cout << result <<std::endl;

return result;
}

/* preProcessor::preProcessor(std::fstream inputfile, int flag)
{

} */

int preProcessor::preProcess(std::vector<std::string> inputVector)
{
    return 0;
}

void str_toupper(std::string& s)
{
    std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){ return std::toupper(c);});
}

