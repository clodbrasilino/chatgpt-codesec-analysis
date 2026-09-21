#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATE_LENGTH 11
#define YEAR_LEN 4
#define MONTH_LEN 2
#define DAY_LEN 2

int convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL) {
        return -1;
    }
    
    size_t len = strnlen(input, DATE_LENGTH);
    if (len != 10) {
        return -1;
    }
    
    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }
    
    for (int i = 0; i < 10; i++) {
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
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_str[YEAR_LEN + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_str[MONTH_LEN + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_str[DAY_LEN + 1];
    
    memset(year_str, 0, sizeof(year_str));
    memset(month_str, 0, sizeof(month_str));
    memset(day_str, 0, sizeof(day_str));
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year_str, input, YEAR_LEN);
    year_str[YEAR_LEN] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month_str, input + 5, MONTH_LEN);
    month_str[MONTH_LEN] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day_str, input + 8, DAY_LEN);
    day_str[DAY_LEN] = '\0';
    
    char *endptr;
    errno = 0;
    long year = strtol(year_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || year < 0 || year > 9999) {
        return -1;
    }
    
    errno = 0;
    long month = strtol(month_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || month < 1 || month > 12) {
        return -1;
    }
    
    errno = 0;
    long day = strtol(day_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || day < 1 || day > 31) {
        return -1;
    }
    
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[2] = 29;
    }
    
    if (day > days_in_month[month]) {
        return -1;
    }
    
    snprintf(output, output_size, "%02ld-%02ld-%04ld", day, month, year);
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_date[DATE_LENGTH * 2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[DATE_LENGTH];
    
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