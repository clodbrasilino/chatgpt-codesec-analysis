#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int days_in_month(int month, int year) {
    switch (month) {
        case 1:  return 31;
        case 2:  return is_leap_year(year) ? 29 : 28;
        case 3:  return 31;
        case 4:  return 30;
        case 5:  return 31;
        case 6:  return 30;
        case 7:  return 31;
        case 8:  return 31;
        case 9:  return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

bool validate_gregorian_date(int year, int month, int day) {
    if (year < 1 || year > 9999) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    int max_days = days_in_month(month, year);
    if (max_days == 0) {
        return false;
    }
    if (day < 1 || day > max_days) {
        return false;
    }
    return true;
}

int main(void) {
    int test_cases[][3] = {
        {2023, 1, 15},
        {2024, 2, 29},
        {2023, 2, 29},
        {2023, 4, 31},
        {2023, 13, 1},
        {2023, 0, 1},
        {2023, 1, 0},
        {2023, 12, 32},
        {0, 1, 1},
        {10000, 1, 1},
        {2000, 2, 29},
        {1900, 2, 29},
        {2024, 12, 31},
        {2024, 6, 30},
        {2024, 6, 31}
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int year = test_cases[i][0];
        int month = test_cases[i][1];
        int day = test_cases[i][2];
        bool valid = validate_gregorian_date(year, month, day);
        printf("%04d-%02d-%02d: %s\n", year, month, day, valid ? "valid" : "invalid");
    }

    return EXIT_SUCCESS;
}