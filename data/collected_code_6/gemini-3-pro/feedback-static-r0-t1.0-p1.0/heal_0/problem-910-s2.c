#include <stdio.h>
#include <stdbool.h>

bool is_leap_year(int year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}

bool is_valid_date(int year, int month, int day) {
    if (year < 1582) {
        return false;
    }
    if (year == 1582 && (month < 10 || (month == 10 && day < 15))) {
        return false;
    }
    
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
    } else if (month == 2) {
        if (is_leap_year(year)) {
            if (day > 29) {
                return false;
            }
        } else {
            if (day > 28) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int test_cases[][3] = {
        {2023, 10, 31},
        {2024, 2, 29},
        {2023, 2, 29},
        {1582, 10, 14},
        {1582, 10, 15},
        {2000, 1, 1},
        {1900, 2, 29}
    };
    
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        int year = test_cases[i][0];
        int month = test_cases[i][1];
        int day = test_cases[i][2];
        
        if (is_valid_date(year, month, day)) {
            printf("%d-%02d-%02d is valid.\n", year, month, day);
        } else {
            printf("%d-%02d-%02d is invalid.\n", year, month, day);
        }
    }

    return 0;
}