#include <stdio.h>
#include <string.h>

enum {
    DATE_LENGTH = 10,
    DATE_BUFFER_SIZE = DATE_LENGTH + 1,
    LINE_BUFFER_SIZE = DATE_LENGTH + 3
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

static int parse_date(const char input[static DATE_BUFFER_SIZE],
                      int *year, int *month, int *day)
{
    size_t i;
    int parsed_year;
    int parsed_month;
    int parsed_day;

    if (year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    if (memchr(input, '\0', DATE_LENGTH) != NULL ||
        input[DATE_LENGTH] != '\0' ||
        input[4] != '-' ||
        input[7] != '-') {
        return -1;
    }

    for (i = 0; i < DATE_LENGTH; ++i) {
        if (i != 4 && i != 7 &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    parsed_year = (input[0] - '0') * 1000 +
                  (input[1] - '0') * 100 +
                  (input[2] - '0') * 10 +
                  (input[3] - '0');

    parsed_month = (input[5] - '0') * 10 +
                   (input[6] - '0');

    parsed_day = (input[8] - '0') * 10 +
                 (input[9] - '0');

    if (parsed_year < 1 ||
        parsed_month < 1 || parsed_month > 12 ||
        parsed_day < 1 ||
        parsed_day > days_in_month(parsed_year, parsed_month)) {
        return -1;
    }

    *year = parsed_year;
    *month = parsed_month;
    *day = parsed_day;

    return 0;
}

static int format_date(char output[static DATE_BUFFER_SIZE],
                       int year, int month, int day)
{
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

static int convert_date(const char input[static DATE_BUFFER_SIZE],
                        char output[static DATE_BUFFER_SIZE])
{
    int year;
    int month;
    int day;

    output[0] = '\0';

    if (parse_date(input, &year, &month, &day) != 0) {
        return -1;
    }

    return format_date(output, year, month, day);
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' ? 0 : -1;
}

static int read_date(char buffer[static DATE_BUFFER_SIZE])
{
    char line[LINE_BUFFER_SIZE];
    size_t length;

    buffer[0] = '\0';

    if (fgets(line, sizeof line, stdin) == NULL) {
        return -1;
    }

    length = strcspn(line, "\r\n");

    if (line[length] == '\0') {
        discard_line();
        return -1;
    }

    if (line[length] == '\r') {
        if (length + 2 >= sizeof line ||
            line[length + 1] != '\n' ||
            line[length + 2] != '\0') {
            discard_line();
            return -1;
        }
    } else {
        if (length + 1 >= sizeof line ||
            line[length + 1] != '\0') {
            discard_line();
            return -1;
        }
    }

    if (length != DATE_LENGTH) {
        return -1;
    }

    for (length = 0; length < DATE_LENGTH; ++length) {
        buffer[length] = line[length];
    }
    buffer[DATE_LENGTH] = '\0';

    return 0;
}

int main(void)
{
    char input[DATE_BUFFER_SIZE] = {0};
    char output[DATE_BUFFER_SIZE] = {0};

    if (read_date(input) != 0 ||
        convert_date(input, output) != 0) {
        if (fputs("Invalid date\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (fputs(output, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        return 1;
    }

    return 0;
}