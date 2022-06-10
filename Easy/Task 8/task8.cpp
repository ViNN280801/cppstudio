#include <iostream>
#include <cmath>

double exponentationFunc(double number, double degree){
    double result = 1;

    for(double i = 0; i < degree; i++)
        result *= number;
    

    return result;
}

void mathExpression(double x, double m, double x_lo, double x_up, double m_lo, double m_up,
    double x_step, double m_step){
    for(double i = x_lo; i <= x_up; i += x_step){
        for(double j = m_lo; j <= m_up; j+= m_step){
            std::cout << "Value of function = " << exponentationFunc(i, j) * 
                exponentationFunc(sin(i * j), j) << "\tm = " << j << std::endl;
        }
        std::cout << "x = " << i << std::endl;
    }
}

int main(){
    double x_step = 0, m_step = 0, x = 0, m = 0, x_lower_interval = 0, x_upper_interval = 0, 
        m_lower_interval = 0, m_upper_interval = 0;

    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter m: ";
    std::cin >> m;

    std::cout << "Enter step for x: ";
    std::cin >> x_step;
    std::cout << "Enter step for m: ";
    std::cin >> m_step;

    std::cout << "Enter x lower interval: ";
    std::cin >> x_lower_interval;
    std::cout << "Enter x upper interval: ";
    std::cin >> x_upper_interval;
    std::cout << "Enter m lower interval: ";
    std::cin >> m_lower_interval;
    std::cout << "Enter m upper interval: ";
    std::cin >> m_upper_interval;
    
    mathExpression(x, m, x_lower_interval, x_upper_interval, m_lower_interval, m_upper_interval, 
        x_step, m_step);

    return EXIT_SUCCESS;
}