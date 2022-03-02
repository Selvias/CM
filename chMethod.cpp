#include "compLinEq.hpp"

int n = 0;
double c = 0;
bool sgn = 0;



void scanFile(std::ifstream *file, std::string *line) {
    while(!(*file).eof()) {
        getline(*file, *line);
    }
}

variable *procesString(std::string line) {

    std::string t;

    for (int i = 0; i < 9; i++) {
        if (line[i] == 'x')
            n++;
    }
    variable *v = new variable [n];
    int shift = 0;
    for (int i = 0; i < (int)line.length(); i++) {
        // std::cout << line[i] << " SH : " << shift << std::endl;
        if (line[i] == '^') {
            int a = 1;
            while (line[i + a] >= 48 && line[i + a] <= 57) {
                t += line[i + a];
                a++;
            }
            i += a - 1;
            // std::cout << a << std::endl;
            v[shift].deg = std::stoi(t);
            t = "";
            // std::cout << v[shift].deg << std::endl;
            shift++;
        }
        // else if (line[i + 1] == 'x') {
        //     if (line[i] >= 48 && line[i] <= 57) {
        //         int a = 0;
        //         while (line[i + a] >= 48 &&  line[i + a] <= 57) {
        //             t += line[i + a];
        //             a++;
        //         }
        //         i += a - 1;
        //         std::cout << a << std::endl;
        //         v[shift].coef = std::stoi(t);
        //         t = "";
        //     }
        //     else
        //         v[shift].coef = 1;
        //     // std::cout << "COEF : " << v[shift].coef << std:: endl;
        // }
        else if (line[i] == 'x')
        {
            // std::cout << i;
            if (i == 0)
                v[shift].coef = 1;
            else {
                // std::cout << "PISOS\n";
                v[shift].deg = 1;
            }
        }
        else if (line[i] == '+' || line[i] == '-') {
            if (line[i] == '+' && !(v[shift].sign))
                v[shift].sign = sgn = 0;
            else
            {
                // std::cout  << shift << " pisos\n";
                v[shift].sign = sgn = 1;
            }
        }
        else {
            // std::cout << line[i] << std::endl;
            if (line[i] >= 48 && line[i] <= 57) {
                int a = 0;
                while (line[i + a] >= 48 &&  line[i + a] <= 57) {
                    t += line[i + a];
                    a++;
                }
                i += a - 1;

                // std::cout << a << std::endl;
                if (i + 1 < (int)line.length())
                    v[shift].coef = std::stoi(t);
                else {
                    if (!sgn)
                        c = std::stoi(t);
                    else
                        c = -1 * std::stoi(t);
                }
                // std::cout << t << std::endl;
            }
            else if (i + 1 < (int)line.length() && line[i + 1] == 'x')
                v[shift].coef = 1;
            t = "";
        }
    }
    return v;
}

double usr_eps(double a, double b) {
    return (std::abs((b - a)/2));
}

double answer(variable *v, double a) {
    double b = 0;

    for (int i = 0; i < n; i++) {
        if (v[i].sign) {
            std::cout << (v[i].coef * (pow(a, v[i].deg))) << std::endl;
            b -= (v[i].coef * (pow(a, v[i].deg)));
            // std::cout << b;
        }
        else {
            b += (v[i].coef * (pow(a, v[i].deg)));
        }
    }
    b += c;

    // std::cout << " B " << b << std::endl;
    return b;
}

double mult_f(double a, double b, double c, variable *v) {
    double fa = answer(v, a) * answer(v, c);
    if (fa < 0)
        return a;
    else
        return b;

}

double half_div_method(variable *v, double a, double b) {
    double C = (a + b) / 2;
    double u_eps = usr_eps(a, b);
        std::cout << "-------------------------" << std::endl;
        std::cout << "C : " << C << std::endl;
        std::cout << "eps : " << u_eps << std::endl;
        std::cout << "A : " << a << std::endl;
        std::cout << "B : " << b << std::endl;
        std::cout << "-------------------------" << std::endl;
    if (u_eps < 0.03)
        return 0;
    else if (mult_f(a, b, C, v) == a)
        return half_div_method(v, a, C);
    else
        return half_div_method(v, C, b);
}