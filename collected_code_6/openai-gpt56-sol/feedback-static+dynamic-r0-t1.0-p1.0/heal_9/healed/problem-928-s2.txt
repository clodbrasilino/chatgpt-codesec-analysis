#include <limits.h>
#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define INPUT_CAPACITY (DATE_LENGTH + 2U)
#define OUTPUT_CAPACITY (DATE_LENGTH + 1U)

static int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int is_leap_year(unsigned int year)
{
    return year % 4U == 0U &&
           (year % 100U != 0U || year % 400U == 0U);
}

static unsigned int days_in_month(unsigned int year, unsigned int month)
{
    static const unsigned int days[] = {
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };

    if (month < 1U || month > 12U) {
        return 0U;
    }

    if (month == 2U && is_leap_year(year)) {
        return 29U;
    }

    return days[month - 1U];
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_date(char *buffer, size_t capacity, size_t *length)
{
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL ||
        capacity < DATE_LENGTH + 1U) {
        return -1;
    }

    *length = 0U;
    used = 0U;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || used == 0U) {
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            ch = fgetc(stdin);

            if (ch == EOF) {
                if (ferror(stdin)) {
                    return -1;
                }
                break;
            }

            if (ch != '\n') {
                if (discard_line() != 0) {
                    return -1;
                }
                return -1;
            }

            break;
        }

        if (used >= capacity - 1U) {
            if (discard_line() != 0) {
                return -1;
            }
            return -1;
        }

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *length = used;
    return 0;
}

static int convert_date(const char *input, size_t input_size,
                        char *output, size_t output_size)
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    int written;

    if (input == NULL || output == NULL ||
        input_size != DATE_LENGTH ||
        output_size < OUTPUT_CAPACITY) {
        return -1;
    }

    if (!is_digit(input[0]) || !is_digit(input[1]) ||
        !is_digit(input[2]) || !is_digit(input[3]) ||
        input[4] != '-' ||
        !is_digit(input[5]) || !is_digit(input[6]) ||
        input[7] != '-' ||
        !is_digit(input[8]) || !is_digit(input[9])) {
        return -1;
    }

    year = (unsigned int)(input[0] - '0') * 1000U +
           (unsigned int)(input[1] - '0') * 100U +
           (unsigned int)(input[2] - '0') * 10U +
           (unsigned int)(input[3] - '0');

    month = (unsigned int)(input[5] - '0') * 10U +
            (unsigned int)(input[6] - '0');

    day = (unsigned int)(input[8] - '0') * 10U +
          (unsigned int)(input[9] - '0');

    if (year == 0U || month < 1U || month > 12U ||
        day < 1U || day > days_in_month(year, month)) {
        return -1;
    }

    written = snprintf(output, output_size, "%02u-%02u-%04u",
                       day, month, year);

    if (written < 0 || (size_t)written != DATE_LENGTH ||
        (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_CAPACITY] = {0};
    char output[OUTPUT_CAPACITY] = {0};
    size_t length;

    if (read_date(input, sizeof input, &length) != 0 ||
        length != DATE_LENGTH ||
        convert_date(input, length, output, sizeof output) != 0) {
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