#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10
#define BUFFER_SIZE (DATE_LENGTH + 2)

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int convert_date(const char input[static DATE_LENGTH + 1],
                        char *output,
                        size_t output_size)
{
    static const int days_per_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int year;
    int month;
    int day;
    int maximum_day;
    int written;

    if (output == NULL || output_size < DATE_LENGTH + 1) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (size_t i = 0; i < DATE_LENGTH; ++i) {
        if (i != 4 && i != 7 &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    if (input[DATE_LENGTH] != '\0') {
        return -1;
    }

    year = (input[0] - '0') * 1000 +
           (input[1] - '0') * 100 +
           (input[2] - '0') * 10 +
           (input[3] - '0');
    month = (input[5] - '0') * 10 + (input[6] - '0');
    day = (input[8] - '0') * 10 + (input[9] - '0');

    if (year < 1 || month < 1 || month > 12) {
        return -1;
    }

    maximum_day = days_per_month[month - 1];
    if (month == 2 && is_leap_year(year)) {
        maximum_day = 29;
    }

    if (day < 1 || day > maximum_day) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d",
                       day, month, year);
    if (written != DATE_LENGTH) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[BUFFER_SIZE];
    char output[DATE_LENGTH + 1];
    size_t newline_position;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return 1;
    }

    newline_position = strcspn(input, "\r\n");

    if (input[newline_position] != '\0') {
        input[newline_position] = '\0';
    } else if (newline_position == sizeof input - 1) {
        int character = getchar();

        if (character != '\n' && character != EOF) {
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            fputs("Invalid date. Expected yyyy-mm-dd.\n", stderr);
            return 1;
        }
    }

    if (convert_date(input, output, sizeof output) != 0) {
        fputs("Invalid date. Expected yyyy-mm-dd.\n", stderr);
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}