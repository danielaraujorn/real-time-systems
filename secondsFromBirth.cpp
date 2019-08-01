// How many seconds do you lived till now?

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{
    time_t current_time;
    struct tm timeinfo={0};
    int day,month,year;

    cout << "Enter your birth day: ";
    cin >> day;
    cout << "Enter your birth month: ";
    cin >> month;
    cout << "Enter your birth year: ";
    cin >> year;

    time(&current_time);

    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;


    cout << difftime(current_time, mktime(&timeinfo)) << " seconds" << endl;

    exit(0);
}