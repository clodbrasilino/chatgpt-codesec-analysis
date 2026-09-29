#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>

static int is_leap_year(unsigned long year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

static int validate_date_parts(unsigned long y, unsigned long m, unsigned long d) {
    if (m < 1 || m > 12 || d < 1 || d > 31) {
        return 0;
    }

    const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned long max_day = (unsigned long)days_in_month[m - 1];

    if (m == 2 && is_leap_year(y)) {
        max_day = 29;
    }

    return d <= max_day;
}

int convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size < 11) {
        return -1;
    }

    size_t input_len = strnlen(input, 11);
    if (input_len != 10) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (size_t i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit((unsigned char)input[i])) {
            return -1;
        }
    }

    unsigned long y = 0;
    unsigned long m = 0;
    unsigned long d = 0;
    char *endptr;

    errno = 0;
    y = strtoul(input, &endptr, 10);
    if (errno == ERANGE || y > 9999 || endptr != input + 4) {
        return -1;
    }

    errno = 0;
    m = strtoul(input + 5, &endptr, 10);
    if (errno == ERANGE || endptr != input + 7) {
        return -1;
    }

    errno = 0;
    d = strtoul(input + 8, &endptr, 10);
    if (errno == ERANGE || endptr != input + 10) {
        return -1;
    }

    if (!validate_date_parts(y, m, d)) {
        return -1;
    }

    int written = snprintf(output, output_size, "%02lu-%02lu-%04lu", d, m, y);
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