#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int calculate_odd_days(int year) {
    int days = is_leap_year(year) ? 366 : 365;
    return days % 7;
}

int main(void) {
    int year;
    
    printf("Enter a year: ");
    if (scanf("%d", &year) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (year < 0) {
        fprintf(stderr, "Year cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    int odd_days = calculate_odd_days(year);
    
    printf("Number of odd days in year %d: %d\n", year, odd_days);
    
    return EXIT_SUCCESS;
}