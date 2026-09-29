#include <stdio.h>
#include <stddef.h>

#define DATE_LENGTH 10U
#define BUFFER_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
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

static int convert_date(const char *input, size_t input_size,
                        char *output, size_t output_size)
{
    int year;
    int month;
    int day;
    int result;

    if (input == NULL || output == NULL ||
        input_size != BUFFER_SIZE || output_size < BUFFER_SIZE) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-' ||
        input[DATE_LENGTH] != '\0') {
        return -1;
    }

    if (parse_digits(input, 4U, &year) != 0 ||
        parse_digits(input + 5, 2U, &month) != 0 ||
        parse_digits(input + 8, 2U, &day) != 0) {
        return -1;
    }

    if (year < 1 || month < 1 || month > 12 ||
        day < 1 || day > days_in_month(year, month)) {
        return -1;
    }

    result = snprintf(output, output_size, "%02d-%02d-%04d",
                      day, month, year);

    if (result != (int)DATE_LENGTH ||
        (size_t)result >= output_size) {
        return -1;
    }

    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch;
}

int main(void)
{
    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];
    size_t length = 0;
    int ch;
    int line_complete = 0;

    while (length < DATE_LENGTH) {
        ch = getchar();

        if (ch == EOF) {
            line_complete = 1;
            break;
        }

        if (ch == '\n') {
            line_complete = 1;
            break;
        }

        if (ch == '\r') {
            ch = getchar();
            if (ch == '\n' || ch == EOF) {
                line_complete = 1;
            } else {
                discard_line();
            }
            break;
        }

        input[length++] = (char)ch;
    }

    input[length] = '\0';

    if (length == DATE_LENGTH && !line_complete) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            line_complete = 1;
        } else if (ch == '\r') {
            ch = getchar();
            if (ch == '\n' || ch == EOF) {
                line_complete = 1;
            } else {
                discard_line();
            }
        } else {
            discard_line();
        }
    }

    if (!line_complete || length != DATE_LENGTH ||
        convert_date(input, sizeof(input), output, sizeof(output)) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}