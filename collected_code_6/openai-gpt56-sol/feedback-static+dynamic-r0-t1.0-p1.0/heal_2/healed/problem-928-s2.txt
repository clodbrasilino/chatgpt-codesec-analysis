#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define BUFFER_SIZE (DATE_LENGTH + 1U)

static int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int days_in_month(int year, int month)
{
    static const int days[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days[month - 1];
}

static int convert_date(const char *input, char *output, size_t output_size)
{
    int year;
    int month;
    int day;
    int written;

    if (input == NULL || output == NULL || output_size < BUFFER_SIZE) {
        return -1;
    }

    if (strnlen(input, BUFFER_SIZE) != DATE_LENGTH) {
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

    year = (input[0] - '0') * 1000 +
           (input[1] - '0') * 100 +
           (input[2] - '0') * 10 +
           (input[3] - '0');

    month = (input[5] - '0') * 10 +
            (input[6] - '0');

    day = (input[8] - '0') * 10 +
          (input[9] - '0');

    if (year < 1 || month < 1 || month > 12 ||
        day < 1 || day > days_in_month(year, month)) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d",
                       day, month, year);

    if (written != (int)DATE_LENGTH || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];
    char line[64];
    size_t length;

    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }

    length = strcspn(line, "\r\n");

    if (line[length] == '\0' && !feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        fputs("Invalid date\n", stderr);
        return 1;
    }

    line[length] = '\0';

    if (length != DATE_LENGTH) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (snprintf(input, sizeof input, "%s", line) != (int)DATE_LENGTH) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (convert_date(input, output, sizeof output) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (fprintf(stdout, "%s\n", output) < 0) {
        return 1;
    }

    return 0;
}