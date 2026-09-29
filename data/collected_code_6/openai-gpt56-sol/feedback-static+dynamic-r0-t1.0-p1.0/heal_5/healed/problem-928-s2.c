#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define INPUT_CAPACITY (DATE_LENGTH + 3U)
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

    if (written < 0 || (size_t)written >= output_size ||
        (size_t)written != DATE_LENGTH) {
        return -1;
    }

    return 0;
}

static int read_date(char *buffer, size_t capacity, size_t *length)
{
    size_t end;

    if (buffer == NULL || length == NULL || capacity < INPUT_CAPACITY) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    end = strcspn(buffer, "\r\n");

    if (buffer[end] == '\r') {
        if (buffer[end + 1U] == '\n') {
            buffer[end + 1U] = '\0';
        } else if (buffer[end + 1U] != '\0') {
            return -1;
        }
        buffer[end] = '\0';
    } else if (buffer[end] == '\n') {
        buffer[end] = '\0';
    } else if (buffer[end] == '\0') {
        int c = fgetc(stdin);

        if (c != '\n' && c != EOF) {
            do {
                c = fgetc(stdin);
            } while (c != '\n' && c != EOF);
            return -1;
        }
    }

    if (ferror(stdin)) {
        return -1;
    }

    *length = end;
    return 0;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    char output[OUTPUT_CAPACITY];
    size_t length;

    if (read_date(input, sizeof input, &length) != 0 ||
        length != DATE_LENGTH ||
        convert_date(input, length, output, sizeof output) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}