#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define BUFFER_SIZE (DATE_LENGTH + 2U)

static int is_leap_year(unsigned int year)
{
    return (year % 4U == 0U && year % 100U != 0U) || year % 400U == 0U;
}

static int convert_date(const char input[static DATE_LENGTH + 1U],
                        char output[static DATE_LENGTH + 1U],
                        size_t output_size)
{
    static const unsigned int days_per_month[] = {
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int max_day;
    size_t i;
    int written;

    if (output_size < DATE_LENGTH + 1U) {
        return -1;
    }

    for (i = 0U; i < DATE_LENGTH; ++i) {
        if (input[i] == '\0') {
            return -1;
        }
    }

    if (input[DATE_LENGTH] != '\0' ||
        input[4] != '-' ||
        input[7] != '-') {
        return -1;
    }

    for (i = 0U; i < DATE_LENGTH; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
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
    if (written != (int)DATE_LENGTH) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[BUFFER_SIZE];
    char output[DATE_LENGTH + 1U];
    size_t length;
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return 1;
    }

    length = strcspn(input, "\r\n");
    if (input[length] == '\0' && length == sizeof input - 1U) {
        character = getchar();
        if (character != '\n' && character != '\r' && character != EOF) {
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            fputs("Invalid date. Expected yyyy-mm-dd.\n", stderr);
            return 1;
        }
    } else {
        input[length] = '\0';
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