#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define INPUT_SIZE (DATE_LENGTH + 2U)
#define OUTPUT_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int convert_date(const char *input, size_t input_length,
                        char *output, size_t output_size)
{
    static const int days_per_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int year;
    int month;
    int day;
    int max_day;
    int written;
    size_t i;

    if (input == NULL || output == NULL ||
        input_length != DATE_LENGTH || output_size < OUTPUT_SIZE) {
        return -1;
    }

    for (i = 0; i < DATE_LENGTH; ++i) {
        if (i == 4U || i == 7U) {
            if (input[i] != '-') {
                return -1;
            }
        } else if (input[i] < '0' || input[i] > '9') {
            return -1;
        }
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

    max_day = days_per_month[month - 1];
    if (month == 2 && is_leap_year(year)) {
        max_day = 29;
    }

    if (day < 1 || day > max_day) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d",
                       day, month, year);
    if (written != (int)DATE_LENGTH) {
        return -1;
    }

    return 0;
}

static int read_date(char *buffer, size_t buffer_size, size_t *length)
{
    char line[INPUT_SIZE];
    size_t len;
    int trailing;

    if (buffer == NULL || length == NULL || buffer_size < INPUT_SIZE) {
        return -1;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        return -1;
    }

    len = strcspn(line, "\r\n");

    if (line[len] == '\r' || line[len] == '\n') {
        line[len] = '\0';

        if (line[len + 1U] == '\n') {
            line[len + 1U] = '\0';
        }
    } else {
        trailing = fgetc(stdin);

        if (trailing == '\r') {
            trailing = fgetc(stdin);
            if (trailing != '\n' && trailing != EOF) {
                while (trailing != '\n' && trailing != EOF) {
                    trailing = fgetc(stdin);
                }
                return -1;
            }
        } else if (trailing != '\n' && trailing != EOF) {
            while (trailing != '\n' && trailing != EOF) {
                trailing = fgetc(stdin);
            }
            return -1;
        }
    }

    if (len >= buffer_size) {
        return -1;
    }

    memcpy(buffer, line, len);
    buffer[len] = '\0';
    *length = len;

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE] = {0};
    char output[OUTPUT_SIZE] = {0};
    size_t input_length = 0U;

    if (read_date(input, sizeof input, &input_length) != 0 ||
        convert_date(input, input_length, output, sizeof output) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (puts(output) == EOF) {
        return 1;
    }

    return 0;
}