#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATE_BUF_SIZE 11
#define INPUT_BUF_SIZE (DATE_BUF_SIZE + 2)

static int is_valid_format(const char *date)
{
    size_t i;

    if (date == NULL) {
        return 0;
    }

    if (strnlen(date, DATE_BUF_SIZE) != 10U) {
        return 0;
    }

    for (i = 0U; i < 10U; i++) {
        if ((i == 4U) || (i == 7U)) {
            if (date[i] != '-') {
                return 0;
            }
        } else {
            if (isdigit((unsigned char)date[i]) == 0) {
                return 0;
            }
        }
    }

    return 1;
}

static int is_valid_date(int year, int month, int day)
{
    static const int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_day;

    if ((year < 1) || (year > 9999)) {
        return 0;
    }

    if ((month < 1) || (month > 12)) {
        return 0;
    }

    max_day = days_in_month[month - 1];

    if (month == 2) {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
            max_day = 29;
        }
    }

    if ((day < 1) || (day > max_day)) {
        return 0;
    }

    return 1;
}

static int convert_date(const char *input, char *output, size_t output_size)
{
    int year;
    int month;
    int day;
    int written;

    if ((input == NULL) || (output == NULL) || (output_size < DATE_BUF_SIZE)) {
        return -1;
    }

    if (is_valid_format(input) == 0) {
        return -1;
    }

    if (sscanf(input, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return -1;
    }

    if (is_valid_date(year, month, day) == 0) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d", day, month, year);

    if ((written < 0) || ((size_t)written >= output_size)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUF_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[DATE_BUF_SIZE] = {0};
    size_t len;

    printf("Enter date (yyyy-mm-dd): ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';

    len = strnlen(input, sizeof(input));

    if ((len > 0U) && (input[len - 1U] == '\n')) {
        input[len - 1U] = '\0';
    }

    if (convert_date(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid date format or value\n");
        return EXIT_FAILURE;
    }

    printf("Converted date: %s\n", output);

    return EXIT_SUCCESS;
}