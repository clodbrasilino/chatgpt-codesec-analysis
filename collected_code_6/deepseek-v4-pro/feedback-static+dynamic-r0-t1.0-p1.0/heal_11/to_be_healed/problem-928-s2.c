#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define DATE_LENGTH 11
#define YEAR_LENGTH 5
#define MONTH_LENGTH 3
#define DAY_LENGTH 3
#define INPUT_DATE_LENGTH 10

static int safe_str_to_int(const char *str, int *value) {
    char *endptr;
    long result;
    
    if (str == NULL || value == NULL) {
        return -1;
    }
    
    if (str[0] == '\0') {
        return -1;
    }
    
    errno = 0;
    result = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || result > INT_MAX || result < INT_MIN) {
        return -1;
    }
    
    if (endptr == str || *endptr != '\0') {
        return -1;
    }
    
    *value = (int)result;
    return 0;
}

static int is_date_valid(int year, int month, int day) {
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (year < 0 || month < 1 || month > 12) {
        return 0;
    }
    
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        days_in_month[2] = 29;
    }
    
    if (day < 1 || day > days_in_month[month]) {
        return 0;
    }
    
    return 1;
}

int convert_date_format(const char *input, char *output, size_t output_size) {
    int year, month, day;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_str[YEAR_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_str[MONTH_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_str[DAY_LENGTH];
    size_t input_len;
    size_t i;
    int written;
    
    if (input == NULL || output == NULL) {
        return -1;
    }
    
    input_len = strnlen(input, INPUT_DATE_LENGTH + 1);
    if (input_len != INPUT_DATE_LENGTH) {
        return -1;
    }
    
    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }
    
    for (i = 0; i < INPUT_DATE_LENGTH; i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (!isdigit((unsigned char)input[i])) {
            return -1;
        }
    }
    
    if (output_size < DATE_LENGTH) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year_str, input, 4);
    year_str[4] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month_str, input + 5, 2);
    month_str[2] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day_str, input + 8, 2);
    day_str[2] = '\0';
    
    if (safe_str_to_int(year_str, &year) != 0) {
        return -1;
    }
    
    if (safe_str_to_int(month_str, &month) != 0) {
        return -1;
    }
    
    if (safe_str_to_int(day_str, &day) != 0) {
        return -1;
    }
    
    if (!is_date_valid(year, month, day)) {
        return -1;
    }
    
    written = snprintf(output, output_size, "%02d-%02d-%04d", day, month, year);
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_date[INPUT_DATE_LENGTH + 2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[DATE_LENGTH];
    size_t len;
    int c;
    
    printf("Enter date (yyyy-mm-dd): ");
    if (fgets(input_date, sizeof(input_date), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    len = strnlen(input_date, sizeof(input_date));
    if (len > 0 && input_date[len - 1] == '\n') {
        input_date[len - 1] = '\0';
    } else {
        if (len == sizeof(input_date) - 1 && input_date[len - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
    }
    
    if (convert_date_format(input_date, output_date, sizeof(output_date)) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return 1;
    }
    
    printf("Converted date: %s\n", output_date);
    
    return 0;
}