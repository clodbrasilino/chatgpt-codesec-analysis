#include <stdio.h>
#include <stdlib.h>

int is_leap_year(int year);
int get_odd_days_in_year(int year);

int is_leap_year(int year) {
    if (year <= 0) {
        return -1;
    }
    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
        return 1;
    }
    return 0;
}

int get_odd_days_in_year(int year) {
    int leap_status = is_leap_year(year);
    if (leap_status == -1) {
        return -1;
    }
    return leap_status ? 2 : 1;
}

int main(void) {
    int year = 2024;
    int odd_days = get_odd_days_in_year(year);

    if (odd_days == -1) {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", odd_days);

    return EXIT_SUCCESS;
}