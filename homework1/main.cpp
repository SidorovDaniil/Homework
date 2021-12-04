#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

int main(){
    std::string path = "in.txt";
    std::ifstream fin;
    fin.open(path);

//    if (fin.is_open()) {
//        double str;
//
//        while (!fin.eof()) {
//
//            fin >> str;
//            std::cout << str << std::endl;
//        }
//    }
    std::cout << "(0,0)";
    return 0;
}
