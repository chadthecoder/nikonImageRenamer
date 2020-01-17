#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string path = fs::current_path();
    //path += "/pics";
    std::cout << path << std::endl << std::endl;
    int test = 0;
    for (const auto & entry : fs::directory_iterator(path))
    {
        std::string fun = entry.path();//.filename();
        std::string fun2 = fun;
        std::transform(fun2.begin(), fun2.end(), fun2.begin(), ::tolower);
        //std::string fun2 = fs::file_status();//entry.path().extension();
        std::cout << fun  << std::endl;
        if(fun2.rfind(".jpg")!=-1)
        {
            std::string num = std::to_string(test);
            while(num.length() < 4)
            {
                num = "0" + num;
            }
            std::cout << std::rename(fun.c_str(), (path + "/DSCN" + num + ".jpg").c_str()) << std::endl;
            std::cout << (path + "/DSCN" + num + ".JPG").c_str() << std::endl;
            test++;
        }
        else if(fun2.rfind(".png")!=-1)
        {
            std::string num = std::to_string(test);
            while(num.length() < 4)
            {
                num = "0" + num;
            }
            std::cout << std::rename(fun.c_str(), (path + "/DSCN" + num + ".PNG").c_str()) << std::endl;
            test++;
        }
        else
        {
            std::cout << "This file does not have a jpg or png file extension." << std::endl;
        }
        std::cout << std::endl;
        //std::cout << entry.path().filename() << std::endl;
    }
        
}