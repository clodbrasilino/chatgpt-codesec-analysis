#include <stdio.h>
#include <stddef.h>

#define DATE_LENGTH 10U
#define INPUT_CAPACITY 64U
#define OUTPUT_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) ||
           (year % 400 == 0);
}

static int days_in_month(int year, int month)
{
    static const int days[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month < 1 || month > 12) {
        return 0;
    }

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days[month - 1];
}

static int parse_digits(const char *text, size_t count, int *value)
{
    size_t i;
    int result = 0;

    if (text == NULL || value == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        unsigned char ch = (unsigned char)text[i];

        if (ch < (unsigned char)'0' || ch > (unsigned char)'9') {
            return -1;
        }

        result = result * 10 + (int)(ch - (unsigned char)'0');
    }

    *value = result;
    return 0;
}

static int discard_remainder_of_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t i;

        for (i = 0U; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                return 0;
            }
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_date(char *input, size_t input_size)
{
    size_t length;

    if (input == NULL || input_size < DATE_LENGTH + 2U) {
        return -1;
    }

    input[0] = '\0';

    if (fgets(input, (int)input_size, stdin) == NULL) {
        return -1;
    }

    for (length = 0U; input[length] != '\0'; ++length) {
        if (input[length] == '\n') {
            input[length] = '\0';

            if (length > 0U && input[length - 1U] == '\r') {
                input[length - 1U] = '\0';
                --length;
            }

            return length == DATE_LENGTH ? 0 : -1;
        }
    }

    if (!feof(stdin)) {
        if (discard_remainder_of_line() != 0) {
            input[0] = '\0';
            return -1;
        }
    }

    if (length > 0U && input[length - 1U] == '\r') {
        input[length - 1U] = '\0';
        --length;
    }

    if (length != DATE_LENGTH) {
        input[0] = '\0';
        return -1;
    }

    return 0;
}

static int convert_date(const char *input, char *output, size_t output_size)
{
    int year;
    int month;
    int day;
    int written;

    if (input == NULL || output == NULL || output_size < OUTPUT_SIZE) {
        return -1;
    }

    if (input[4] != '-' ||
        input[7] != '-' ||
        input[DATE_LENGTH] != '\0') {
        return -1;
    }

    if (parse_digits(input, 4U, &year) != 0 ||
        parse_digits(input + 5, 2U, &month) != 0 ||
        parse_digits(input + 8, 2U, &day) != 0) {
        return -1;
    }

    if (year < 1 ||
        month < 1 ||
        month > 12 ||
        day < 1 ||
        day > days_in_month(year, month)) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d",
                       day, month, year);

    if (written < 0 || (size_t)written >= output_size ||
        written != (int)DATE_LENGTH) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_SIZE];

    if (read_date(input, sizeof(input)) != 0 ||
        convert_date(input, output, sizeof(output)) != 0) {
        if (fputs("Invalid date\n", stderr) == EOF) {
            return 1;
        }

        return 1;
    }

    if (fprintf(stdout, "%s\n", output) < 0) {
        return 1;
    }

    return 0;
}