#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string>

typedef struct {
    double coef;
    int deg;
    bool sign;
} variable;

//поток для чтения,  кол-во строк, кол-во столбцов
void scanFile(std::ifstream *, std::string *);
variable *procesString(std::string line);

double answer(variable *v, double a);

double usr_eps(double, double);

double half_div_method(variable *v, double a, double b);