#include <stdio.h>
#include <stddef.h>

#define DATE_LENGTH 10
#define INPUT_SIZE (DATE_LENGTH + 2)
#define OUTPUT_SIZE (DATE_LENGTH + 1)

static int is_leap_year(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) ||
           (year % 400 == 0);
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

static int convert_date(const char *input, char *output, size_t output_size)
{
    int year;
    int month;
    int day;

    if (input == NULL || output == NULL || output_size < OUTPUT_SIZE) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-' || input[DATE_LENGTH] != '\0') {
        return -1;
    }

    if (parse_digits(input, 4, &year) != 0 ||
        parse_digits(input + 5, 2, &month) != 0 ||
        parse_digits(input + 8, 2, &day) != 0) {
        return -1;
    }

    if (year < 1 || month < 1 || month > 12 ||
        day < 1 || day > days_in_month(year, month)) {
        return -1;
    }

    output[0] = (char)('0' + day / 10);
    output[1] = (char)('0' + day % 10);
    output[2] = '-';
    output[3] = (char)('0' + month / 10);
    output[4] = (char)('0' + month % 10);
    output[5] = '-';
    output[6] = (char)('0' + year / 1000);
    output[7] = (char)('0' + (year / 100) % 10);
    output[8] = (char)('0' + (year / 10) % 10);
    output[9] = (char)('0' + year % 10);
    output[10] = '\0';

    return 0;
}

static int read_date(char *input, size_t input_size)
{
    size_t length = 0;
    int ch;

    if (input == NULL || input_size < DATE_LENGTH + 1) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                while (next != '\n' && next != EOF) {
                    next = getchar();
                }
                return -1;
            }

            break;
        }

        if (length >= DATE_LENGTH) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            return -1;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    if (length != DATE_LENGTH) {
        return -1;
    }

    input[length] = '\0';
    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    char output[OUTPUT_SIZE];

    if (read_date(input, sizeof(input)) != 0 ||
        convert_date(input, output, sizeof(output)) != 0) {
        if (fputs("Invalid date\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        return 1;
    }

    return 0;
}