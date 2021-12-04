#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

std::vector<double> ReadFile(std::string path){

    std::vector<double> coords;
    std::vector<std::string> points;

    std::ifstream fin;
    fin.open(path);

    if (fin.is_open()){
        std::string str;

        while (!fin.eof()) {
            str = "";
            fin >> str;
            points.push_back(str);
        }
    }

    fin.close();

    for (int i; i< points.size(); i++){

        std::string b = points[i];
        double a = strtod(b.c_str(), nullptr);
        coords.push_back(a);
    }

    return coords;
}

std::vector<double> XorY(std::vector<double> coords,int name_of_axis){

    std::vector<double> axis;

    for (int i; i< coords.size()/2; i++){

        if(name_of_axis == 1){              // 1 is equal x
            axis.push_back(coords[2*i]);
        }
        else{                               // 2,3... is equal y
            axis.push_back(coords[2*i+1]);
        }
    }
    return axis;
}

std::vector<double> LeftOrRight(std::vector<double> X, std::vector<double> Y, int name_of_axis, double x0,double y0,std::string LoR){
    std::vector<double> arr;

    for (int i = 0; i< X.size(); i++){
        if ( (x0 > 0 && y0 >= 0) || (x0 > 0 && y0 <= 0 ) ){
            if ((x0 * Y[i] < y0 * X[i]) && (LoR == "R")) { //Right, LoR = 1 <=> Right
                if (name_of_axis == 1) { //name_of_axis = 1 <=> X
                    arr.push_back(X[i]);
                } else {
                    arr.push_back(Y[i]);
                }
            }

            if( (x0 * Y[i] > y0 * X[i]) && (LoR == "L") ){ //Left LoR = L <=> Left
                if (name_of_axis == 1){ //name_of_axis = 1 <=> X
                    arr.push_back(X[i]);
                } else{
                    arr.push_back(Y[i]);
                }
            }
        }

        if ((x0 <= 0 && y0 >= 0) || (x0 <= 0 && y0 <= 0 )){
            if ((x0 * Y[i] < y0 * X[i]) && (LoR == "R")) { //Right, LoR = 1 <=> Right
                if (name_of_axis == 1) { //name_of_axis = 1 <=> X
                    arr.push_back(X[i]);
                } else {
                    arr.push_back(Y[i]);
                }
            }

            if( (x0 * Y[i] > y0 * X[i]) && (LoR == "L") ){ //Left LoR = L <=> Left
                if (name_of_axis == 1){ //name_of_axis = 1 <=> X
                    arr.push_back(X[i]);
                } else{
                    arr.push_back(Y[i]);
                }
            }
        }

        if( (x0 * Y[i] == y0 * X[i]) && (LoR == "M") ){
            if (name_of_axis == 1){
                arr.push_back(X[i]);
            } else{
                arr.push_back(Y[i]);
            }
        }

    }

    return arr;
}

int left_right_most(std::vector<double> X , std::vector<double> Y,double x0, double y0){
    std::vector<double> angle;
    double up;
    double down;
    double m;
    int currentMaxIndex = 0;
    for(int i = 0; i < X.size(); i++){

        up = x0 * X[i] + y0 * Y[i];
        down = sqrt(pow(x0,2) + pow(y0,2)) * sqrt(pow(X[i],2) + pow(Y[i],2));
        m = acos(up/down);
        angle.push_back(m);
    }

    for (int i = 0; i < angle.size(); i++) {
        if(angle[i] > angle[currentMaxIndex]){
            currentMaxIndex = i;
        }
    }
    return currentMaxIndex;
}

int main() {
    std::string path = "in.txt";
    double x0, y0;

    std::vector<double> X_left;
    std::vector<double> Y_left;
    std::vector<double> X_right;
    std::vector<double> Y_right;
    std::vector<double> X_mid;
    std::vector<double> Y_mid;
    std::vector<double> angle_right;
    std::vector<double> angle_left;

    std::vector<double> coords = ReadFile(path);

    x0 = coords[0];
    y0 = coords[1];

    coords.erase(coords.begin() + 0);
    coords.erase(coords.begin() + 0);

    std::vector<double> X = XorY(coords, 1);
    std::vector<double> Y = XorY(coords, 2);

    //std::cout <<"X0= " << x0 << " and Y0= "<< y0 << std::endl;

    X_right = LeftOrRight(X,Y,1,x0,y0,"R");
    Y_right = LeftOrRight(X,Y,2,x0,y0,"R");

    X_left = LeftOrRight(X,Y,1,x0,y0,"L");
    Y_left = LeftOrRight(X,Y,2,x0,y0,"L");

    X_mid = LeftOrRight(X,Y,1,x0,y0,"M");
    Y_mid = LeftOrRight(X,Y,2,x0,y0,"M");
/*
    std::cout <<X_right.size()<<std::endl;
    for (int i = 0; i < X_right.size(); i++){
        std::cout << "(X_right(i),Y_right(i)) "<<"(" << X_right[i] << "," << Y_right[i] << ")" << std::endl;
    }
    std::cout <<X_left.size()<<std::endl;
    for (int i = 0; i < X_left.size(); i++){
        std::cout << "(X_left(i),Y_left(i)) "<<"(" << X_left[i] << "," << Y_left[i] << ")" << std::endl;
    }

    std::cout <<X_mid.size()<<std::endl;
    for (int i = 0; i < X_mid.size(); i++){
        std::cout << "(X_mid(i),Y_mid(i)) "<<"(" << X_mid[i] << "," << Y_mid[i] << ")" << std::endl;
    }
*/
    int LM = left_right_most(X_left,Y_left,x0,y0);
    int RM = left_right_most(X_right,Y_right,x0,y0);
    int MM = left_right_most(X_mid,Y_mid,x0,y0);

    double a,b,c,d,e,r;
    a = X_mid[MM];
    b = Y_mid[MM];

    if( !X_right.empty() && !Y_right.empty()){
        c = X_right[RM];
        d = Y_right[RM];
    } else {
        c = 0;
        d = 0;
    }

    if( !X_left.empty() && !Y_left.empty()){
        e = X_left[LM];
        r = Y_left[LM];
    } else {
        e = 0;
        r = 0;
    }

    if ((X_mid[MM] * x0 < 0) || (Y_mid[MM] * y0 < 0) ){
        c = a;
        d = b;

    }

    std::cout <<"Leftmost: " << e <<" " << r << std::endl;
    std::cout <<"Rightmost: " << c <<" " << d << std::endl;

    return 0;
}

