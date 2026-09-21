#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define BUFFER_SIZE (DATE_LENGTH + 1U)

static int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int convert_date(const char input[static BUFFER_SIZE],
                        char output[static BUFFER_SIZE],
                        size_t output_size)
{
    int year;
    int month;
    int day;
    int written;
    size_t length;

    if (output_size < BUFFER_SIZE) {
        return -1;
    }

    length = strnlen(input, BUFFER_SIZE);
    if (length != DATE_LENGTH) {
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

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d",
                       day, month, year);

    if (written < 0 || (size_t)written >= output_size ||
        (size_t)written != DATE_LENGTH) {
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

    if (line[length] == '\0' && length == sizeof line - 1U) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid date\n", stderr);
        return 1;
    }

    line[length] = '\0';

    if (length != DATE_LENGTH) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    memcpy(input, line, DATE_LENGTH);
    input[DATE_LENGTH] = '\0';

    if (convert_date(input, output, sizeof output) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}