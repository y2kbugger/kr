#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy this defect.
 */

static char daytab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/* day_of_year:  return day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (month < 1 || 12 < month)
        return 0;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (day < 1 || daytab[leap][month] < day)
        return 0;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (yearday < 1 || 365 + leap < yearday) {
        *pmonth = 0;
        *pday = 0;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

void test_doy(int year, int month, int day, int expected)
{
    int doy = day_of_year(year, month, day);
    printf("%d:%d\n", doy, expected);
}

void test_md(int year, int yearday, int expected_month, int expected_day)
{
    int pmonth = 0;
    int pday = 0;
    month_day(year, yearday, &pmonth, &pday);
    printf("%d:%d, %d:%d\n", pmonth, expected_month, pday, expected_day);
}


int main()
{
    test_doy(2019, 1, 1, 1);
    test_doy(2019, -1, 1, 0);
    test_doy(2019, 1, -1, 0);
    test_doy(2019, 1, 2, 2);
    test_doy(2019, 2, 1, 32);
    test_doy(2019, 62, 1, 0);
    test_doy(2019, 2, 28, 59);
    test_doy(2019, 2, 29, 0);
    test_md(2019, 32, 2, 1);
    test_md(2019, 366, 0, 0);
    test_md(2019, 0, 0, 0);
    test_md(2019, -1, 0, 0);
}
