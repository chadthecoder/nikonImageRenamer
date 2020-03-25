#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
using std::cout;
using namespace boost::filesystem;

int main(int argc, char* argv[])
{


  path p (".");

      if (is_directory(p))
      {
        cout << p << " is a directory containing:\n";

        std::vector<path> v;

        for (auto&& x : directory_iterator(p))
          v.push_back(x.path()); 

        std::sort(v.begin(), v.end());  

        for (auto&& x : v)
          cout << "    " << x.filename() << '\n';
      }
  return 0;
}

/*
#include <exiv2/exiv2.hpp>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <algorithm>
#include <filesystem>

//added because the program needs c++-17 for the filesystem library but auto_ptr is deprecated in c++-17
#define std::unique_ptr      auto_ptr

#if defined(EXV_UNICODE_PATH) && defined(__MINGW__)
#undef  EXV_UNICODE_PATH
#endif
#ifdef  EXV_UNICODE_PATH
#define _tchar      wchar_t
#define _tstrcmp    wcscmp
#define _t(s)       L##s
#define _tcout      wcout
#define _tmain      wmain
#else
#define _tchar      char
#define _tstrcmp    strcmp
#define _t(s)       s
#define _tcout      cout
#define _tmain      main
#endif

int func(std::string fileName)
{
    try
    {
        /*
        const _tchar* prog = argv[0];
        const _tchar* file = argv[1];
        if (argc != 2)
        {
            std::_tcout << _t("Usage: ") << prog << _t(" [ file | --version || --version-test ]") << std::endl;
            return 1;
        }
        if ( _tstrcmp(file,_t("--version")) == 0 )
        {
            exv_grep_keys_t keys;
            Exiv2::dumpLibraryInfo(std::cout,keys);
            return 0;
        }
        else if ( _tstrcmp(file,_t("--version-test")) == 0 )
        {
            // verifies/test macro EXIV2_TEST_VERSION
            // described in include/exiv2/version.hpp
            std::cout << "EXV_PACKAGE_VERSION             " << EXV_PACKAGE_VERSION             << std::endl
                    << "Exiv2::version()                " << Exiv2::version()                << std::endl
                    << "strlen(Exiv2::version())        " << ::strlen(Exiv2::version())      << std::endl
                    << "Exiv2::versionNumber()          " << Exiv2::versionNumber()          << std::endl
                    << "Exiv2::versionString()          " << Exiv2::versionString()          << std::endl
                    << "Exiv2::versionNumberHexString() " << Exiv2::versionNumberHexString() << std::endl
                    ;
            // Test the Exiv2 version available at runtime but compile the if-clause only if
            // the compile-time version is at least 0.15. Earlier versions didn't have a
            // testVersion() function:
            #if EXIV2_TEST_VERSION(0,15,0)
                if (Exiv2::testVersion(0,13,0))
                {
                    std::cout << "Available Exiv2 version is equal to or greater than 0.13\n";
                }
                else
                {
                    std::cout << "Installed Exiv2 version is less than 0.13\n";
                }
            #else
                std::cout << "Compile-time Exiv2 version doesn't have Exiv2::testVersion()\n";
            #endif
            return 0;
        }
        

        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(fileName);
        assert(image.get() != 0);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty())
        {
            std::string error("No Exif data found in file");
            throw Exiv2::Error(Exiv2::kerErrorMessage, error);
        }
        Exiv2::ExifData::const_iterator end = exifData.end();
        for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i)
        {
            const char* tn = i->typeName();
            std::cout << std::setw(44) << std::setfill(' ') << std::left
                    << i->key() << " "
                    << "0x" << std::setw(4) << std::setfill('0') << std::right
                    << std::hex << i->tag() << " "
                    << std::setw(9) << std::setfill(' ') << std::left
                    << (tn ? tn : "Unknown") << " "
                    << std::dec << std::setw(3)
                    << std::setfill(' ') << std::right
                    << i->count() << "  "
                    << std::dec << i->value()
                    << "\n";
        }
        return 0;
    }
    //catch (std::exception& e) {
    //catch (Exiv2::AnyError& e) {
    catch (Exiv2::Error& e)
    {
        std::cout << "Caught Exiv2 exception '" << e.what() << "'\n";
        return -1;
    }
}

//namespace fs = std::filesystem;

int _tmain(int argc, _tchar* const argv[]) {
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
            func(fileName2);

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
*/

/*
#include <exiv2/exiv2.hpp>
#include <iostream>
#include <iomanip>
#include <cassert>
#if defined(EXV_UNICODE_PATH) && defined(__MINGW__)
#undef  EXV_UNICODE_PATH
#endif
#ifdef  EXV_UNICODE_PATH
#define _tchar      wchar_t
#define _tstrcmp    wcscmp
#define _t(s)       L##s
#define _tcout      wcout
#define _tmain      wmain
#else
#define _tchar      char
#define _tstrcmp    strcmp
#define _t(s)       s
#define _tcout      cout
#define _tmain      main
#endif

int _tmain(int argc, _tchar* const argv[])
try {
    const _tchar* prog = argv[0];
    const _tchar* file = argv[1];
    if (argc != 2) {
        std::_tcout << _t("Usage: ") << prog << _t(" [ file | --version || --version-test ]") << std::endl;
        return 1;
    }
    if ( _tstrcmp(file,_t("--version")) == 0 ) {
        exv_grep_keys_t keys;
        Exiv2::dumpLibraryInfo(std::cout,keys);
        return 0;
    } else if ( _tstrcmp(file,_t("--version-test")) == 0 ) {
        // verifies/test macro EXIV2_TEST_VERSION
        // described in include/exiv2/version.hpp
        std::cout << "EXV_PACKAGE_VERSION             " << EXV_PACKAGE_VERSION             << std::endl
                  << "Exiv2::version()                " << Exiv2::version()                << std::endl
                  << "strlen(Exiv2::version())        " << ::strlen(Exiv2::version())      << std::endl
                  << "Exiv2::versionNumber()          " << Exiv2::versionNumber()          << std::endl
                  << "Exiv2::versionString()          " << Exiv2::versionString()          << std::endl
                  << "Exiv2::versionNumberHexString() " << Exiv2::versionNumberHexString() << std::endl
                  ;
        // Test the Exiv2 version available at runtime but compile the if-clause only if
        // the compile-time version is at least 0.15. Earlier versions didn't have a
        // testVersion() function:
        #if EXIV2_TEST_VERSION(0,15,0)
            if (Exiv2::testVersion(0,13,0)) {
              std::cout << "Available Exiv2 version is equal to or greater than 0.13\n";
            } else {
              std::cout << "Installed Exiv2 version is less than 0.13\n";
            }
        #else
              std::cout << "Compile-time Exiv2 version doesn't have Exiv2::testVersion()\n";
        #endif
        return 0;
    }
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
    assert(image.get() != 0);
    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        std::string error("No Exif data found in file");
        throw Exiv2::Error(Exiv2::kerErrorMessage, error);
    }
    Exiv2::ExifData::const_iterator end = exifData.end();
    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
        const char* tn = i->typeName();
        std::cout << std::setw(44) << std::setfill(' ') << std::left
                  << i->key() << " "
                  << "0x" << std::setw(4) << std::setfill('0') << std::right
                  << std::hex << i->tag() << " "
                  << std::setw(9) << std::setfill(' ') << std::left
                  << (tn ? tn : "Unknown") << " "
                  << std::dec << std::setw(3)
                  << std::setfill(' ') << std::right
                  << i->count() << "  "
                  << std::dec << i->value()
                  << "\n";
    }
    return 0;
}
//catch (std::exception& e) {
//catch (Exiv2::AnyError& e) {
catch (Exiv2::Error& e) {
    std::cout << "Caught Exiv2 exception '" << e.what() << "'\n";
    return -1;
}
*/

/*
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
*/