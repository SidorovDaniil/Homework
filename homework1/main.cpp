#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

int main(){
    std::string path = "in.txt";
    std::ifstream fin;
    fin.open(path);

    //первые два числа из файла
    double x0;
    double y0;

    //пара чисел, находящихся слева
    double x_left = 0;
    double y_left = 0;

    //пара чисел, находящихся справа
    double x_right = 0;
    double y_right = 0;

    //Переменные, содержащие ответ на задачу
    double max_x_r = 0;
    double max_y_r = 0;

    double max_x_l = 0;
    double max_y_l = 0;

    double norm1;
    double norm2;

    double angle_r = 1;
    double angle_l = 1;

    double angleR0 = 1;
    double angleL0 = 1;

    //Вспомогательные переменные
    double x1;
    double y1;

    if (fin.is_open()) {

        //Координаты направляющего вектора
        fin >> x0;
        fin >> y0;
//        std::cout << "x0 = " << x0 << std::endl;
//        std::cout << "y0 = " << y0 << std::endl;

        norm1 = sqrt(x0 * x0 + y0 * y0);

        while (!fin.eof()){
            fin >> x1;
            fin >> y1;
            norm2 = sqrt(x1 * x1 + y1 * y1);
//            std::cout << "x1 = " << x1 << " y1 = " << y1 << std::endl;
//            std::cout << "norm2= " << norm2 <<std::endl;


            //Направляющий вектор лежит в 1 или 4 четверти
            if ( (y0 >= 0 && x0 > 0) || (y0 < 0 && x0 >= 0) ){
                if ( y1 * x0 <= x1 * y0){
                    x_right = x1;
                    y_right = y1;

                    angle_r = (x0 * x1 + y0 * y1)/(norm1 * norm2);

//                    std::cout << "this point right "<<std::endl;

//                    std::cout << "angleR= " << angle_r <<std::endl;
                }

                if (y1 * x0 > x1 * y0){
                    x_left = x1;
                    y_left = y1;

                    angle_l = (x0 * x1 + y0 * y1)/(norm1 * norm2);

//                    std::cout << "this point left "<<std::endl;
//
//                    std::cout << "angleL= " << angle_l <<std::endl;
                }
            }

            //Направляющий вектор лежит в 2 или 3 четверти
            if ( (y0 <= 0 && x0 < 0) || (y0 > 0 && x0 <= 0) ){
                if ( y1 * x0 <= x1 * y0){
                    x_right = x1;
                    y_right = y1;

                    angle_r = (x0 * x1 + y0 * y1)/(norm1 * norm2);

//                    std::cout << "this point right "<<std::endl;
//                    std::cout << "angleR= " << angle_r <<std::endl;
                }

                if (y1 * x0 > x1 * y0){
                    x_left = x1;
                    y_left = y1;

                    angle_l = (x0 * x1 + y0 * y1)/(norm1 * norm2);

//                    std::cout << "this point left "<<std::endl;
//                    std::cout << "angleL= " << angle_l <<std::endl;

                }
            }

            if (angle_r <= angleR0){

                angleR0 = angle_r;
                max_x_r = x_right;
                max_y_r = y_right;
            }

            if (angle_l <= angleL0){
                angleL0 = angle_l;
                max_x_l = x_left;
                max_y_l = y_left;
            }

        }
    }

    else{
        std::cout<< "No file";
    }
    std::cout << "Leftmost: "<< max_x_l << " " << max_y_l <<std::endl;
    std::cout << "Rightmost: " << max_x_r << " " << max_y_r<<std::endl;

    fin.close();
    return 0;
}
