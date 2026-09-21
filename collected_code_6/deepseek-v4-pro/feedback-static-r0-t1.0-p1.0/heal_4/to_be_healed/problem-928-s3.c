#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11) {
        return -1;
    }

    size_t len = 0;
    const char *p = input;
    while (len < 11 && *p != '\0') {
        len++;
        p++;
    }
    if (len != 10) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (input[i] < '0' || input[i] > '9') {
            return -1;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_str[5] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_str[3] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_str[3] = {0};

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year_str, input, 4);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month_str, input + 5, 2);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day_str, input + 8, 2);

    char *endptr;
    long y = strtol(year_str, &endptr, 10);
    if (*endptr != '\0' || y < 0 || y > 9999) {
        return -1;
    }

    long m = strtol(month_str, &endptr, 10);
    if (*endptr != '\0' || m < 1 || m > 12) {
        return -1;
    }

    long d = strtol(day_str, &endptr, 10);
    if (*endptr != '\0' || d < 1) {
        return -1;
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int leap = ((int)y % 4 == 0 && (int)y % 100 != 0) || ((int)y % 400 == 0);
    if (leap && m == 2) {
        days_in_month[1] = 29;
    }

    if (d > days_in_month[m - 1]) {
        return -1;
    }

    int written = snprintf(output, output_size, "%s-%s-%s", day_str, month_str, year_str);
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

int main(void) {
    const char *input_date = "2024-03-15";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[11] = {0};

    if (convert_date_format(input_date, output_date, sizeof(output_date)) == 0) {
        printf("%s\n", output_date);
    } else {
        fprintf(stderr, "Invalid date format\n");
        return 1;
    }

    return 0;
}