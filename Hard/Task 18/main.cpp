#include "PlottingTheFunc.hpp"

int main(int argc, char *argv[])
{
    int16_t *x = returnInterval();
    double *y = calcValuesOfFunc();

    string fileName = plotFunction(x, y);
    exeScrpitOnLinux(fileName);
    exeScrpitOnWindows(fileName);

    return EXIT_SUCCESS;
}