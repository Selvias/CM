#include "compLinEq.hpp"

int main() {

    std::ifstream input;
    input.open("linear_eq.txt");

    std::string line;
    scanFile(&input, &line);
    std::cout << line << std::endl;

    variable *v = procesString(line);

    // half_div_method(v, 1, 2);

    // hord_method(v, 1, 2);
    
    newton_method(v, 1, 2, 0.001);

    input.close();

    return 0;
}