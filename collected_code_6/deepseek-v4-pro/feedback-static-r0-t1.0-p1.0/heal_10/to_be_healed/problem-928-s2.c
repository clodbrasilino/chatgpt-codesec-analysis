#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATE_LENGTH 11
#define YEAR_LEN 4
#define MONTH_LEN 2
#define DAY_LEN 2
#define INPUT_DATE_LEN 12
#define TEMP_BUFFER_SIZE 5

static int is_leap_year(long year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int validate_date_parts(long year, long month, long day) {
    static const int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month < 1 || month > 12) {
        return 0;
    }
    
    if (day < 1) {
        return 0;
    }
    
    int max_day = days_in_month[month];
    if (month == 2 && is_leap_year(year)) {
        max_day = 29;
    }
    
    if (day > max_day) {
        return 0;
    }
    
    return 1;
}

static int parse_date_component(const char *str, size_t len, long *value) {
    if (len == 0 || len >= TEMP_BUFFER_SIZE) {
        return -1;
    }
    
    if (str == NULL || value == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[TEMP_BUFFER_SIZE] = {0};
    
    size_t i;
    for (i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        }
        temp[i] = str[i];
    }
    temp[len] = '\0';
    
    char *endptr;
    errno = 0;
    
    *value = strtol(temp, &endptr, 10);
    
    if (errno != 0 || *endptr != '\0') {
        return -1;
    }
    
    return 0;
}

int convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL) {
        return -1;
    }
    
    size_t len = strnlen(input, INPUT_DATE_LEN);
    if (len != 10) {
        return -1;
    }
    
    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }
    
    int i;
    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (input[i] < '0' || input[i] > '9') {
            return -1;
        }
    }
    
    if (output_size < DATE_LENGTH) {
        return -1;
    }
    
    long year, month, day;
    
    if (parse_date_component(input, YEAR_LEN, &year) != 0) {
        return -1;
    }
    
    if (year < 0 || year > 9999) {
        return -1;
    }
    
    if (parse_date_component(input + 5, MONTH_LEN, &month) != 0) {
        return -1;
    }
    
    if (parse_date_component(input + 8, DAY_LEN, &day) != 0) {
        return -1;
    }
    
    if (!validate_date_parts(year, month, day)) {
        return -1;
    }
    
    int written = snprintf(output, output_size, "%02ld-%02ld-%04ld", day, month, year);
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_date[INPUT_DATE_LEN] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[DATE_LENGTH] = {0};
    
    printf("Enter date (yyyy-mm-dd): ");
    if (fgets(input_date, sizeof(input_date), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input_date[strcspn(input_date, "\n")] = '\0';
    
    if (convert_date_format(input_date, output_date, sizeof(output_date)) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return 1;
    }
    
    printf("Converted date: %s\n", output_date);
    
    return 0;
}