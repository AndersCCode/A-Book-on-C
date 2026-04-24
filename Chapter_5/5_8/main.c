/* There is no error checking in day_of_year or month_day. Remedy this effect. */

#include <stdio.h>


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},        // non-leap year
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}         // leap year
};

/* Given a date, it calculates waht day of the year it is (1 = Jan 1, 32 = Feb 1, 
365 or 366 = Dec 31 */

int day_of_year(int year, int month, int day) {
    int i, leap;

    if (year <= 0) {
        printf("Error: invalid year %d\n", year);
        return -1;
    }
    
    if (month < 1 || month > 12) {
        printf("Error: invalid month %d\n", month);
        return -1;
    }

    if (day < 1) {
        printf("Error: invalid day %d\n", day);
        return -1;
    }

    /* Determine if it's a leap year
     Leap year if evenly divisible by 4 and not evenly divisible by 100 (2024, 2028, 2032...)
     OR it is evenly divisible by 400 (special century years 2000, 2400, 2800...) */
    leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);  

    // Key check to reject April 31, June 31, Februrary 30, etc.
    if (day > daytab[leap][month]) {
        printf("Error: invalid date %d-%02d-%02d \n"
                        "(month %d has only %d days)\n",
                        year, month, day, month, daytab[leap][month]);
        return -1;
    }

    // Add up all the days from previous months
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    
    return day;     // return the total
}

/* Given a year and a day-of-the-year (e.g. 222) it calculates which month and day it is */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    if (pmonth == NULL || pday == NULL) {
        printf("Error: NULL pointer passed to pmonth or pday\n");
        return;
    }

    if (year <= 0) {
        printf("Error: invalid year %d\n", year);
        *pmonth = 1;
        *pday = 1;
        return;
    }

    /* Determine if it's a leap year
     Leap year if evenly divisible by 4 and not evenly divisible by 100 (2024, 2028, 2032...)
     OR it is evenly divisible by 400 (special century years 2000, 2400, 2800...) */
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    int maxdays = leap ? 366 : 365;

    if (yearday < 1 || yearday > maxdays) {
        printf("Error: yearday %d is out of range (1..%d)\n", yearday, maxdays);
        *pmonth = 1;
        *pday = 1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    
    *pmonth = i;
    *pday = yearday;
}

int main(void) {

    int month, day;

    printf("\nDay of Year\n");
    printf("-----------\n");
    printf("2018-06-31 = day %d\n", day_of_year(2018, 6, 30));
    printf("2026-04-22 = day %d\n\n", day_of_year(2026, 4, 22));
    
    printf("Test of invalid dates\n");
    printf("---------------------\n");
    day_of_year(2026, 4, 31);       // April 31
    day_of_year(2026, 6, 31);       // June 31
    day_of_year(2026, 2, 29);       // February 29

    printf("\nWhich day was it?\n");
    printf("-----------------\n");
    month_day(2026, 222, &month, &day);

    if (month == -1) 
        printf("Invalid yearday\n");
    else 
        printf("Day 222 in 2025 was month %d and day %d\n\n", month, day);

    return 0;
}