#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define DATE_LEN 11

static int is_valid_format(const char *date)
{
    size_t i;

    if (date == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(date) != DATE_LEN - 1) {
        return 0;
    }

    for (i = 0; i < DATE_LEN - 1; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') {
                return 0;
            }
        } else {
            if (!isdigit((unsigned char)date[i])) {
                return 0;
            }
        }
    }

    return 1;
}

static int is_valid_date(int year, int month, int day)
{
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return 0;
    }

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29;
    }

    if (day > days_in_month[month - 1]) {
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

    if (input == NULL || output == NULL || output_size < DATE_LEN) {
        return -1;
    }

    if (!is_valid_format(input)) {
        return -1;
    }

    if (sscanf(input, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return -1;
    }

    if (!is_valid_date(year, month, day)) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d", day, month, year);
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[DATE_LEN];

    printf("Enter date (yyyy-mm-dd): ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (convert_date(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid date: %s\n", input);
        return EXIT_FAILURE;
    }

    printf("Converted date: %s\n", output);

    return EXIT_SUCCESS;
}