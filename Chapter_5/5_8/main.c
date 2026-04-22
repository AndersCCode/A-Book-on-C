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

    // Determine if it's a leap year
    leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    
    return day;
}

/* set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    
    *pmonth = i;
    *pday = yearday;
}

int main(void) {

    int month, day;

    printf("2018-06-31 = day %d\n", day_of_year(2018, 6, 31));
    printf("2026-04-22 = day %d\n", day_of_year(2026, 4, 22));

    month_day(2026, 222, &month, &day);

    if (month == -1) {
        printf("Invalid yearday\n");
    } else {
        printf("Day 222 in 2025 was month %d and day %d\n", month, day);
    }

    return 0;
}