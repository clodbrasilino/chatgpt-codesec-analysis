#include <stdio.h>

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int odd_days(int year) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 50550500 * 365 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:321,execs:154,op:havoc,rep:2)
     */
    int days = year * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    int weeks = days / 7;
    int odd_day_count = days - (weeks * 7);
    if (is_leap_year(year)) {
        odd_day_count++;
    }
    return odd_day_count % 7;
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    printf("Number of odd days in %d: %d\n", year, odd_days(year));
    return 0;
}