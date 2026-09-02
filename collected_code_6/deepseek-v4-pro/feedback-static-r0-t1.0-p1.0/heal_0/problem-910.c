#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool is_leap_year(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

bool validate_gregorian_date(int year, int month, int day) {
    if (year < 1 || year > 9999) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;
    
    static const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int max_day = days_in_month[month - 1];
    
    if (month == 2 && is_leap_year(year)) {
        max_day = 29;
    }
    
    if (day > max_day) return false;
    
    struct tm time_info = {0};
    time_info.tm_year = year - 1900;
    time_info.tm_mon = month - 1;
    time_info.tm_mday = day;
    
    time_t raw_time = mktime(&time_info);
    if (raw_time == (time_t)-1) return false;
    
    struct tm *check_time = localtime(&raw_time);
    if (check_time == NULL) return false;
    
    if (check_time->tm_year != year - 1900 ||
        check_time->tm_mon != month - 1 ||
        check_time->tm_mday != day) {
        return false;
    }
    
    return true;
}

int main(void) {
    int test_dates[][3] = {
        {2023, 1, 15},
        {2023, 2, 29},
        {2024, 2, 29},
        {2023, 4, 31},
        {2023, 13, 1},
        {2023, 0, 15},
        {2023, 1, 0},
        {2023, 12, 31},
        {1, 1, 1},
        {9999, 12, 31},
        {10000, 1, 1},
        {0, 1, 1}
    };
    
    int num_tests = sizeof(test_dates) / sizeof(test_dates[0]);
    
    for (int i = 0; i < num_tests; i++) {
        bool is_valid = validate_gregorian_date(test_dates[i][0], 
                                                test_dates[i][1], 
                                                test_dates[i][2]);
        printf("%04d-%02d-%02d: %s\n", 
               test_dates[i][0], 
               test_dates[i][1], 
               test_dates[i][2],
               is_valid ? "valid" : "invalid");
    }
    
    return 0;
}