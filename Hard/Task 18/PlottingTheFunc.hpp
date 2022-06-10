#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr int16_t minValueOfInterval{-50};
constexpr int16_t maxValueOfInterval{50};

// Returning array of int16_t from -50 to 50
int16_t *returnInterval()
{
    int16_t *interval = new int16_t[101];

    for (int16_t iter = 0; iter <= maxValueOfInterval * 2; iter++)
    {
        *(interval + iter) = iter - 50;
    }

    return interval;
}

// Calculating values of func y = 2sin(x)exp(4/5), returns array of double
double *calcValuesOfFunc()
{
    // Declaring vector of doubles (50 negative, null and 50 positive)
    double *dArr = new double[101];

    // Calculating all values with loop for()
    for (int16_t iter = 0; iter <= maxValueOfInterval * 2; iter++)
    {
        // Adding values one by one to vector
        *(dArr + iter) = 2 * sin(iter - 50) * exp(4.0 / 5.0);
    }

    return dArr;
}

// Create file with gnuplot script, returns name of file
string plotFunction(const int16_t *__x, const double *__y)
{
    // Declaring file output stream and name of file
    ofstream fout;
    string fileName("data.txt");

    try
    {
        // Attempt to open file
        fout.open(fileName);

        // Writing matrix into a file
        for (int16_t iter = 0; iter <= maxValueOfInterval * 2; iter++)
        {
            fout << *(__x + iter) << " " << *(__y + iter) << endl;
        }

        cout << "File " << fileName << " has been successfully created. " << endl;
    }
    catch (const ofstream::failure &err)
    {
        cerr << "Error: " << err.what() << endl;
        cerr << "Code of error: " << err.code() << endl;
    }

    // Closing opened file
    fout.close();

    return fileName;
}

// Execute srcipt which plotting function
void exeScrpitOnLinux(const string &__fileName)
{
    // Defining file output stream
    ofstream fout;
    string scriptName("script.gpi");

    try
    {
        // Attempting to open a file
        fout.open(scriptName);

        // Pointing on gnuplot for work with it
        fout << "#! /usr/bin/gnuplot -persist" << endl;

        // Resetting settings (for avoid undefined behavior)
        fout << "reset" << endl;

        // Setting names of axes
        fout << "set xlabel \"rad\" font \"Times New Roman, 14\"" << endl;
        fout << "set xlabel \"value\" font \"Times New Roman, 14\"" << endl;

        // Setting grid
        fout << "set grid" << endl;

        // Setting range for X axis
        fout << "set xrange[-50.0:50]" << endl;
        fout << "set yrange[]" << endl;

        // Setting title
        fout << "set title \"2*sin(x)*exp(4/5)\" font \"Times New Roman, 20\"" << endl;

        // Plotting using data from file and connecting points with straight lines
        fout << "plot \"data.txt\" using 1:2 with linespoint" << endl;
    }
    catch (const ofstream::failure &err)
    {
        cerr << "Error: " << err.what() << endl;
        cerr << "Code of error: " << err.code() << endl;
    }

    fout.close();

    // Making file executive
    string commandLine("chmod +x ");
    commandLine += scriptName;

    // Execute command to make a file executive
    system(commandLine.c_str());

    // Zeroing out string
    commandLine.clear();

    // Executing script
    commandLine = "./" + scriptName;

    system(commandLine.c_str());

    commandLine.clear();
}

// Execute srcipt which plotting function
void exeScrpitOnWindows(const string &__fileName)
{
    // Defining file output stream
    ofstream fout;
    string scriptName("script.txt");

    // Declaring needed string for plotting using data from file and connecting points with straight lines
    string plotCommand("reset\nset xlabel \"rad\" font \"Times New Roman, 14\"\nplot \"data.txt\" using 1:2 with linespoint");

    try
    {
        // Attempting to open a file
        fout.open(scriptName);

        // Resetting settings (for avoid undefined behavior)
        fout << "reset" << endl;

        // Setting names of axes
        fout << "set xlabel \"rad\" font \"Times New Roman, 14\"" << endl;
        fout << "set xlabel \"value\" font \"Times New Roman, 14\"" << endl;

        // Setting grid
        fout << "set grid" << endl;

        // Setting range for X axis
        fout << "set xrange[-50.0:50]" << endl;
        fout << "set yrange[]" << endl;

        // Setting title
        fout << "set title \"2*sin(x)*exp(4/5)\" font \"Times New Roman, 20\"" << endl;
    }
    catch (const ofstream::failure &err)
    {
        cerr << "Error: " << err.what() << endl;
        cerr << "Code of error: " << err.code() << endl;
    }

    fout.close();

    cout << "Enter lines from " << scriptName << "\nThen, enter this line: " << plotCommand << endl;
    system("gnuplot");
}