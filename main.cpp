#include "compLinEq.hpp"

int main() {

    std::ifstream input;
    input.open("linear_eq.txt");

    std::string line;
    scanFile(&input, &line);
    std::cout << line << std::endl;

    variable *v = procesString(line);

    half_div_method(v, 1, 2);
    
    input.close();

    return 0;
}