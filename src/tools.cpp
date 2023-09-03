#include"tools.h"
// #include<iostream>

std::vector<std::string> fileSizeSuffix({"B", "K", "M", "G", "T", "P"});

std::string convertFileSize(fileSize_t size)
{
    // fileSize_t step = 1, _size = size;
    std::string res;
    for (int i = 0; i < fileSizeSuffix.size(); ++i)
    {
        // _size /=;
        // step *= 1024;
        if (size / 1024 > 0)
        {
            size /= 1024;
            continue;
        }
        res = std::to_string(size) + fileSizeSuffix[i];
        break;

    }
    return res;
}


// int main()
// {
//     fileSize_t t = 100000000;
//     std::string s = convertFileSize(t);
//     std::cout << "res: " << s << std::endl;
//     return 0;
// }