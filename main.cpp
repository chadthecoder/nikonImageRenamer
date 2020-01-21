#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>

//namespace fs = std::filesystem;

int main() {
    std::string path = std::filesystem::current_path();
    //path += "/pics";
    std::cout << path << std::endl << std::endl;
    int numInt = 0;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        std::string fileName1 = entry.path();//.filename();
        std::string fileName2 = fileName1;
        std::transform(fileName2.begin(), fileName2.end(), fileName2.begin(), ::tolower);
        //std::string fileName2 = fs::file_status();//entry.path().extension();
        std::cout << fileName1  << std::endl;
        if(fileName2.rfind(".jpg")!=-1)
        {
            std::string numString = std::to_string(numInt);
            while(numString.length() < 4)
            {
                numString = "0" + numString;
            }
            std::cout << std::rename(fileName1.c_str(), (path + "/DSCN" + numString + ".jpg").c_str()) << std::endl;
            std::cout << (path + "/DSCN" + numString + ".JPG").c_str() << std::endl;
            numInt++;
        }
        else if(fileName2.rfind(".png")!=-1)
        {
            std::string numString = std::to_string(numInt);
            while(numString.length() < 4)
            {
                numString = "0" + numString;
            }
            std::cout << std::rename(fileName1.c_str(), (path + "/DSCN" + numString + ".PNG").c_str()) << std::endl;
            numInt++;
        }
        else
        {
            std::cout << "This file does not have a jpg or png file extension." << std::endl;
        }
        std::cout << std::endl;
        //std::cout << entry.path().filename() << std::endl;
    }
        
}
