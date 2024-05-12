#pragma once
#include <string>

// Get the code from a file
std::string read_f(std::fstream& file){
    std::string buffer;
    std::string code = "";
    while (std::getline(file,buffer))
    {   // filters out preprocesses
        if(buffer[0] == '#')
            continue;
        
        code.append(buffer);
        code.append("\n");
    }
    return code;
}
