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

static int convert_date(const char *input, char *output, size_t output_size)
{
    static const unsigned int days_per_month[12] = {
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int maximum_day;
    int written;
    size_t i;

    if (input == NULL || output == NULL ||
        output_size < OUTPUT_BUFFER_SIZE) {
        return -1;
    }

    if (strnlen(input, DATE_LENGTH + 1U) != DATE_LENGTH) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
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

    maximum_day = days_per_month[month - 1U];
    if (month == 2U && is_leap_year(year)) {
        maximum_day = 29U;
    }

    if (day == 0U || day > maximum_day) {
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

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char output[OUTPUT_BUFFER_SIZE];
    char *line_end;
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return 1;
    }

    line_end = strpbrk(input, "\r\n");
    if (line_end != NULL) {
        *line_end = '\0';
    } else if (strnlen(input, sizeof input) == sizeof input - 1U) {
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

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