#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10
#define INPUT_SIZE (DATE_LENGTH + 2)
#define OUTPUT_SIZE (DATE_LENGTH + 1)

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int convert_date(const char input[static DATE_LENGTH + 1],
                        char output[static OUTPUT_SIZE],
                        size_t output_size)
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

    if (output_size < OUTPUT_SIZE) {
        return -1;
    }

    if (input[0] < '0' || input[0] > '9' ||
        input[1] < '0' || input[1] > '9' ||
        input[2] < '0' || input[2] > '9' ||
        input[3] < '0' || input[3] > '9' ||
        input[4] != '-' ||
        input[5] < '0' || input[5] > '9' ||
        input[6] < '0' || input[6] > '9' ||
        input[7] != '-' ||
        input[8] < '0' || input[8] > '9' ||
        input[9] < '0' || input[9] > '9' ||
        input[10] != '\0') {
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

    max_day = days_per_month[month - 1];
    if (month == 2 && is_leap_year(year)) {
        max_day = 29;
    }

    if (day < 1 || day > max_day) {
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
    char input[INPUT_SIZE];
    char output[OUTPUT_SIZE];
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    length = strcspn(input, "\r\n");

    if (input[length] != '\0') {
        input[length] = '\0';
        if (input[length + 1] == '\r' || input[length + 1] == '\n') {
            ch = (unsigned char)input[length + 1];
            if ((input[length] == '\r' && ch != '\n') ||
                (input[length] == '\n' && ch != '\r')) {
                ungetc(ch, stdin);
            }
        }
    } else if (length == sizeof input - 1) {
        ch = getchar();
        if (ch != '\n' && ch != '\r' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fputs("Invalid date\n", stderr);
            return 1;
        }
        if (ch == '\r') {
            ch = getchar();
            if (ch != '\n' && ch != EOF) {
                ungetc(ch, stdin);
            }
        }
    }

    if (convert_date(input, output, sizeof output) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (puts(output) == EOF) {
        return 1;
    }

    return 0;
}