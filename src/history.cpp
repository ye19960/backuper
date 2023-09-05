#include"history.h"
#include<stdio.h>
#define BUFF_SIZE 512

std::vector<std::vector<std::string>> history::load(std::string path){
    std::ifstream historyStream(path);
    if (!historyStream.is_open()){
        std::cout << "load history file fail." << std::endl;
    }
    char buff[BUFF_SIZE];
    std::string strBuff;
    while(!historyStream.eof()){
        historyStream.getline(buff, BUFF_SIZE);
        

    }
}