#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define DATE_INPUT_LEN 10U
#define OUTPUT_MIN_SIZE 11U
#define INPUT_BUF_SIZE 32U
#define OUTPUT_BUF_SIZE 16U

int convert_date(const char *input, char *output, size_t output_size);

int convert_date(const char *input, char *output, size_t output_size)
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    size_t i;
    size_t len;
    int written;
    static const unsigned int days_in_month[12] = {
        31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U
    };

    if (input == NULL || output == NULL) {
        return -1;
    }

    if (output_size < OUTPUT_MIN_SIZE) {
        return -1;
    }

    len = strnlen(input, DATE_INPUT_LEN + 1U);
    if (len != DATE_INPUT_LEN) {
        return -1;
    }

    for (i = 0U; i < DATE_INPUT_LEN; i++) {
        if (i == 4U || i == 7U) {
            if (input[i] != '-') {
                return -1;
            }
        } else {
            if (!isdigit((unsigned char)input[i])) {
                return -1;
            }
        }
    }

    if (sscanf(input, "%4u-%2u-%2u", &year, &month, &day) != 3) {
        return -1;
    }

    if (year < 1U || year > 9999U) {
        return -1;
    }

    if (month < 1U || month > 12U) {
        return -1;
    }

    if (day < 1U || day > days_in_month[month - 1U]) {
        return -1;
    }

    if (month == 2U && day == 29U) {
        if (!((year % 4U == 0U && year % 100U != 0U) || (year % 400U == 0U))) {
            return -1;
        }
    }

    written = snprintf(output, output_size, "%02u-%02u-%04u", day, month, year);
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_BUF_SIZE];
    char output[OUTPUT_BUF_SIZE];

    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));

    printf("Enter date (yyyy-mm-dd): ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';
    input[strcspn(input, "\n")] = '\0';

    if (convert_date(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    return EXIT_SUCCESS;
}