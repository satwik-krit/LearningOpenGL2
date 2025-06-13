#include <fstream>
#include <string>
#include <iostream>
#include <string_view>
#include <sstream>

#include "glad/glad.h"

#include "Util.h"
#include "Types.h"

std::string read_file_contents(std::string_view file_path)
{
    std::string line;
    std::ifstream file(file_path.data());
    std::stringstream sstream;

    if (file.is_open())
    {
        sstream << file.rdbuf();
        // if (!file.eof())
        // {
        //     std::cout << "ERROR::FILE\n" << "Did not reach EOF: " << file_path << '\n';
        // }

        file.close();
        return sstream.str();
    } 

    std::cout << "ERROR::FILE\n" << "Failed to open file " << file_path << '\n';
    return "";
}

