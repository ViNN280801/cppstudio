#include <iostream>

// Returns pair of symbols which are representating number of quarter
// If none of checks aren't valid -> return "Unknown"
const char *quarter_number(const double &__x = 0.0, const double &__y = 0.0)
{
    // Checking all values
    if (__x == 0.0 && __y == 0.0)
        return "OO";
    // 1st quarter if both of values are positive
    else if (__x > 0.0 && __y > 0.0)
        return "I";
    // If X < 0 and Y > 0 -> value is in a 2nd qarter
    else if (__x < 0.0 && __y > 0.0)
        return "II";
    // If X < 0 and Y < 0 -> value is in a 3rd qarter
    else if (__x < 0.0 && __y < 0.0)
        return "III";
    // 4th quarter if both of values are negative
    else if (__x > 0.0 && __y < 0.0)
        return "IV";
    // If X > 0 and y = 0 -> value is on a positive part of X axis
    else if (__x > 0.0 && __y == 0.0)
        return "+OX";
    // If X = 0 and y > 0 -> value is on a positive part of Y axis
    else if (__x == 0.0 && __y > 0.0)
        return "+OY";
    // If X < 0 and y = 0 -> value is on a negative part of X axis
    else if (__x < 0.0 && __y == 0.0)
        return "-OX";
    // If X = 0 and y < 0 -> value is on a negative part of Y axis
    else if (__x == 0.0 && __y < 0.0)
        return "-OY";
    // If none of checks aren't valid -> return "Unknown"
    else
        return "Unknown";
}

int main()
{
    // Initializing array of double values to check all of quarters and places on a coordinate system
    const double double_arr[]{0.0, 0.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, -1.0};

    // Checking of all quarters with 'for' loop
    for (unsigned short int next = 0U; next < 18U; next++)
    {
        // Output result in terminal
        std::cout << quarter_number(double_arr[next], double_arr[next + 1]) << std::endl;
        
        // Incrementing next value to skip unnecessary
        next++;
    }

    return EXIT_SUCCESS;
}