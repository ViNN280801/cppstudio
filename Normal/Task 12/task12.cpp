// Task: To develop a program in which the menu will be organized,
// the selection of menu functions should be organized by the function key.
// All information should be stored in an array of structures, with the
// possibility of writing them to a file. Organize data sorting by various
// methods (fast, Shell, Bubble), the output of the sorting results should be in tabular form.

// Compile: gcc task12.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include "task12.hpp"

int main()
{
    Employee employee;
    
    unsigned int choice{employee.print_menu()};
    employee.do_option(choice);

    return EXIT_SUCCESS;
}