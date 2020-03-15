/*
 * Nicole Zhang
 * nj3zhang
 */

#ifndef data_h
#define data_h
#include <iostream>
#include <string.h>
using namespace std;

struct XY {
    double x;
    double y;
};
class city_info {
public:
    string name;
    double x;
    double y;
    int population;
    int costLL;
    int salary;
    city_info(){
        name = "";
        x = 0;
        y = 0;
        population = 0;
        costLL = 0;
        salary = 0;
    };
    city_info (string n, double x1, double y1, int p, int r, int s){
        name = n;
        x = x1;
        y = y1;
        population = p;
        costLL = r;
        salary = s;
    }
};
#endif 

