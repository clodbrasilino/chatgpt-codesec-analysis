#include <stdio.h>

int is_leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

int odd_days_in_year(int year) {
    int total_days = is_leap_year(year) ? 366 : 365;
    return total_days % 7;
}

int main(void) {
    int year;
    int result;
    
    printf("Enter a year: ");
    if (scanf("%d", &year) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (year < 1) {
        fprintf(stderr, "Year must be positive\n");
        return 1;
    }
    
    result = odd_days_in_year(year);
    printf("Number of odd days in %d: %d\n", year, result);
    
    return 0;
}