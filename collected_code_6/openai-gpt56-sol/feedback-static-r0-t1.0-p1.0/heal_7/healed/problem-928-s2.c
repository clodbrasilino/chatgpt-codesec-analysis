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

    for (i = 0; i < count; ++i) {
        if (text[i] < '0' || text[i] > '9') {
            return -1;
        }

        result = result * 10 + (text[i] - '0');
    }

    *value = result;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_date(char *input, size_t input_size)
{
    size_t length = 0;
    int ch;

    if (input == NULL || input_size < DATE_LENGTH + 1U) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U >= input_size) {
            if (discard_line() != 0) {
                return -1;
            }
            input[0] = '\0';
            return -1;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        input[0] = '\0';
        return -1;
    }

    if (ch == EOF && length == 0U) {
        input[0] = '\0';
        return -1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    return length == DATE_LENGTH ? 0 : -1;
}

static int convert_date(const char *input, char *output, size_t output_size)
{
    int year;
    int month;
    int day;

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

    if (snprintf(output, output_size, "%02d-%02d-%04d",
                 day, month, year) != (int)DATE_LENGTH) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_CAPACITY];
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