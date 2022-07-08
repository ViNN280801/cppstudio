// Task: Create a test-program: questions appear on the screen in turn (questions are selected by the programmer), with answer options.
// At the end of the work, the program gives out the number of points earned based on the results of the answer.

#include <iostream>
#include <string>

// Array that stores correct answers
constexpr int correct_answers[3]{9, 100, 340};

// Returns true if string is a number
bool is_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Using 'while' loop to check if all symbols in string are digits
    while (it != __str.end() && std::isdigit(*it))
    {
        // Incrementing iterator
        ++it;
    }

    return !__str.empty() && it == __str.end();
}

// Returns true if entered value is integer number
bool validate_integer(const std::string &__number)
{
    if (is_number(__number))
        return true;
    else
        return false;
}

// Returns true if answer is correct, false if answer is incorrect
bool is_correct_answer(const int &__number_of_question, const std::string &__answer)
{
    // Stores integer representation of string answer
    int answer{std::stoi(__answer)};

    switch (__number_of_question)
    {
    case 1:
        switch (answer)
        {
        case 5:
            return false;
        case 7:
            return false;
        case 9:
            return true;
        default:
            return false;
        }
        break;
    case 2:
        switch (answer)
        {
        case 10:
            return false;
        case 100:
            return true;
        case 1000:
            return false;
        default:
            return false;
        }
        break;
    case 3:
        switch (answer)
        {
        case 340:
            return true;
        case 320:
            return false;
        case 240:
            return false;
        default:
            return false;
        }
        break;
    default:
        return false;
    }
}

// Returns count of correct answers
unsigned short int test()
{
    // User's choice variable
    std::string choice{};

    // Count of correct answers
    unsigned int correct{};

    std::cout << "Hint: You need to entered numeric answer.\n1) How many cat lives?\n-> 5 lives\n-> 7 lives\n-> 9 lives\n";
    std::cin >> choice;

    // If 'choice' is an integer number and if it is a correct answer -> incrementing counter of correct answers
    if (validate_integer(choice) && is_correct_answer(1, choice))
        correct++;

    std::cout << "Hint: You need to entered numeric answer.\n2) How many centimeters in a meter?\n-> 10 centimeters\n-> 100 centimeters\n-> 1000 centimeters\n";
    std::cin >> choice;

    if (validate_integer(choice) && is_correct_answer(2, choice))
        correct++;

    std::cout << "Hint: You need to entered numeric answer.\n3) The speed of sound?\n-> 340 m/s\n-> 320 m/s\n-> 240 m/s\n";
    std::cin >> choice;
    
    if (validate_integer(choice) && is_correct_answer(3, choice))
        correct++;

    // Returning count of correct answers
    return correct;
}

int main()
{
    // Variable that stores count of correct answers
    unsigned short int correct{test()};

    // Printing message to terminal
    std::cout << "Count of correct answers: " << correct << std::endl;

    return EXIT_SUCCESS;
}
