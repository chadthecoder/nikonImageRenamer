#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main() {
    std::string path = fs::current_path();
    for (const auto & entry : fs::directory_iterator(path))
    {
        std::string fun = entry.path().filename();
        std::cout << fun << std::endl;
        if(fun.rfind(".jpg")==-1)
        {
            std::cout << "yeehaw" << std::endl;
        }
        std::cout << std::endl;
        //std::cout << entry.path().filename() << std::endl;
    }
        
}