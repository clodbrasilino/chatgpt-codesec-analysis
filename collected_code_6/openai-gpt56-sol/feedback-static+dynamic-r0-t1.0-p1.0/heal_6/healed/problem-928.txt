#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define INPUT_BUFFER_SIZE (DATE_LENGTH + 2U)
#define OUTPUT_BUFFER_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(unsigned int year)
{
    return year % 4U == 0U &&
           (year % 100U != 0U || year % 400U == 0U);
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch;
}

static int read_date(char *buffer, size_t buffer_size)
{
    size_t length;
    int ch;

    if (buffer == NULL || buffer_size < INPUT_BUFFER_SIZE ||
        buffer_size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (buffer[length] == '\r') {
        buffer[length] = '\0';

        if (buffer[length + 1U] == '\n') {
            buffer[length + 1U] = '\0';
        } else {
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                discard_line();
                return -1;
            }
        }
    } else {
        ch = fgetc(stdin);

        if (ch == '\r') {
            ch = fgetc(stdin);
        }

        if (ch != '\n' && ch != EOF) {
            discard_line();
            return -1;
        }
    }

    return length == DATE_LENGTH ? 0 : -1;
}

static int convert_date(const char *input, char *output, size_t output_size)
{
    static const unsigned int days_per_month[12] = {
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int max_day;
    size_t i;
    int written;

    if (input == NULL || output == NULL ||
        output_size < OUTPUT_BUFFER_SIZE) {
        return -1;
    }

    for (i = 0U; i < DATE_LENGTH; ++i) {
        if (i == 4U || i == 7U) {
            if (input[i] != '-') {
                return -1;
            }
        } else if (input[i] < '0' || input[i] > '9') {
            return -1;
        }
    }

    if (input[DATE_LENGTH] != '\0') {
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

    if (year == 0U || month == 0U || month > 12U) {
        return -1;
    }

    max_day = days_per_month[month - 1U];

    if (month == 2U && is_leap_year(year)) {
        max_day = 29U;
    }

    if (day == 0U || day > max_day) {
        return -1;
    }

    written = snprintf(output, output_size, "%02u-%02u-%04u",
                       day, month, year);

    if (written < 0 || (size_t)written >= output_size ||
        written != (int)DATE_LENGTH) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE] = {0};
    char output[OUTPUT_BUFFER_SIZE] = {0};

    if (read_date(input, sizeof input) != 0 ||
        convert_date(input, output, sizeof output) != 0) {
        if (fputs("Invalid date\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (puts(output) == EOF) {
        return 1;
    }

    return 0;
}