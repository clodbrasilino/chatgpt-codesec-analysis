#include <stdio.h>
#include <string.h>

enum {
    DATE_LENGTH = 10,
    INPUT_SIZE = DATE_LENGTH + 2,
    OUTPUT_SIZE = DATE_LENGTH + 1
};

static int is_leap_year(int year)
{
    return year % 4 == 0 &&
           (year % 100 != 0 || year % 400 == 0);
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

static int parse_date(const char input[static DATE_LENGTH + 1],
                      int *year, int *month, int *day)
{
    size_t i;

    if (input == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (i = 0; i < DATE_LENGTH; ++i) {
        if (i != 4 && i != 7 &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    *year = (input[0] - '0') * 1000 +
            (input[1] - '0') * 100 +
            (input[2] - '0') * 10 +
            (input[3] - '0');

    *month = (input[5] - '0') * 10 +
             (input[6] - '0');

    *day = (input[8] - '0') * 10 +
           (input[9] - '0');

    if (*year < 1 ||
        *month < 1 || *month > 12 ||
        *day < 1 || *day > days_in_month(*year, *month)) {
        return -1;
    }

    return 0;
}

static int convert_date(const char *input, size_t input_size,
                        char *output, size_t output_size)
{
    int year;
    int month;
    int day;
    int written;
    size_t length;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    output[0] = '\0';

    if (input_size < DATE_LENGTH + 1 ||
        output_size < OUTPUT_SIZE) {
        return -1;
    }

    length = strnlen(input, input_size);
    if (length != DATE_LENGTH) {
        return -1;
    }

    if (parse_date(input, &year, &month, &day) != 0) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d",
                       day, month, year);

    if (written != DATE_LENGTH || (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

static int read_date(char *buffer, size_t buffer_size)
{
    char line[256];
    size_t length;

    if (buffer == NULL || buffer_size < DATE_LENGTH + 1) {
        return -1;
    }

    buffer[0] = '\0';

    if (fgets(line, sizeof line, stdin) == NULL) {
        return -1;
    }

    length = strcspn(line, "\r\n");

    if (line[length] == '\0' && length == sizeof line - 1) {
        return -1;
    }

    if (line[length] == '\r' && line[length + 1] != '\n' &&
        line[length + 1] != '\0') {
        return -1;
    }

    if (length != DATE_LENGTH || length + 1 > buffer_size) {
        return -1;
    }

    memcpy(buffer, line, length);
    buffer[length] = '\0';

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE] = {0};
    char output[OUTPUT_SIZE] = {0};

    if (read_date(input, sizeof input) != 0 ||
        convert_date(input, sizeof input, output, sizeof output) != 0) {
        if (fputs("Invalid date\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}