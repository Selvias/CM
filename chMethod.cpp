#include "compLinEq.hpp"

#define dv_f(_x) 3 * _x * _x
#define dv_f2(_x) 6 * _x

int n = 0;
double c = 0;
bool sgn = 0;

double xk = 0;
double xk1 = 0;

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

double comp_f(variable *v, double a) {
    double b = 0;

    for (int i = 0; i < n; i++) {
        if (v[i].sign) {
            std::cout << (v[i].coef * (pow(a, v[i].deg))) << std::endl;
            b -= (v[i].coef * (pow(a, v[i].deg)));
        }
        else {
            b += (v[i].coef * (pow(a, v[i].deg)));
        }
    }
    b += c;

    return b;
}

double mult_f(double a, double b, double c, variable *v) {
    double fa = comp_f(v, a) * comp_f(v, c);
    if (fa < 0)
        return a;
    else
        return b;

}

// double dv_f(variable *v, double x, double h) {
//     return ((comp_f(v, x + h) - comp_f(v, x - h)) / 2 * h);
// }

// double dv_f2(variable *v, double x, double h) {
//     return ((comp_f(v, x + h) - 2 * comp_f(v, x) + comp_f(v, x - h)) / h * h);
// }

double half_div_method(variable *v, double a, double b, double eps) {
    double C = (a + b) / 2;
    double u_eps = usr_eps(a, b);
        std::cout << "-------------------------" << std::endl;
        std::cout << "C : " << C << std::endl;
        std::cout << "eps : " << u_eps << std::endl;
        std::cout << "A : " << a << std::endl;
        std::cout << "B : " << b << std::endl;
        std::cout << "-------------------------" << std::endl;
    if (u_eps < eps)
        return 0;
    else if (mult_f(a, b, C, v) == a)
        return half_div_method(v, a, C, eps);
    else
        return half_div_method(v, C, b, eps);
}

double hord_method(variable *v, double a, double b, double eps) {
    double C = (((a * comp_f(v, b)) - (b * comp_f(v, a))) / (comp_f(v, b) - comp_f(v, a)));
    double u_eps = usr_eps(a, b);
        std::cout << "-------------------------" << std::endl;
        std::cout << "C : " << C << std::endl;
        std::cout << "eps : " << u_eps << std::endl;
        std::cout << "A : " << a << std::endl;
        std::cout << "B : " << b << std::endl;
        std::cout << "-------------------------" << std::endl;
    if (u_eps < eps)
        return 0;
    else if (mult_f(a, b, C, v) == a)
        return hord_method(v, a, C, eps);
    else
        return hord_method(v, C, b, eps);
}

double newton_method(variable *v, double a, double b, double eps) {
    double u_eps = std::abs(b - a);
        double res_fa = comp_f(v, a);
        // double res_f2a = dv_f2(v, a, 1);
        double res_f2a = dv_f2(a);
        if ((res_fa >= 0 && res_f2a >= 0) || (res_fa < 0 && res_f2a < 0)) {
            xk = a;
            // xk1 = (xk - (res_fa / dv_f(v, xk, 1)));
            xk1 = (xk - (res_fa / dv_f(xk)));
        }
        else {
            xk = b;
            double t1 = dv_f(xk);
            double t2 = comp_f(v, b);
            // xk1 = (xk - ((comp_f(v, b)) / dv_f(v, xk, 0.9637)));
            xk1 = (xk - (t2 / t1));
        }

    std::cout << xk1 << std::endl;
    // std::cout << (comp_f(v, b)) << std::endl;
    // std::cout << dv_f(v, xk, 0.9637) << std::endl;
    // std::cout << dv_f2(v, xk, 0.9637) << std::endl;

    int i = 2;
    double t1 = 0;
    double t2 = 0;

    do {
        xk = xk1;
        t1 = dv_f(xk);
        t2 = comp_f(v, xk);
        // xk1 = (xk - ((comp_f(v, xk)) / dv_f(v, xk, 0.9637)));
        xk1 = (xk - (t2 / t1));
        std::cout << "X" << i << " : " << xk1 << std::endl;
        u_eps = std::abs(xk1 - xk);
    } while (u_eps > eps);

    return 0;
}