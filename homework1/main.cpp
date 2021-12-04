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
//    else{
//        std::cout<< "No file";
//    }
    std::cout << "Leftmost: "<< 0 << " " << 0 <<std::endl;
    std::cout << "Rightmost: " << 0 << " " << 0 <<std::endl;


    return 0;
}
