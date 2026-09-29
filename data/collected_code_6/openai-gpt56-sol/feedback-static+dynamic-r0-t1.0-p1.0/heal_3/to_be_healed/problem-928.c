#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10
#define INPUT_SIZE (DATE_LENGTH + 2)
#define OUTPUT_SIZE (DATE_LENGTH + 1)

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int convert_date(const char *input, size_t input_length,
                        char *output, size_t output_size)
{
    static const int days_per_month[12] = {
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
        if (i == 4 || i == 7) {
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
    if (written < 0 || (size_t)written >= output_size ||
        written != DATE_LENGTH) {
        return -1;
    }

    return 0;
}

static int read_date(char *buffer, size_t buffer_size, size_t *length)
{
    int ch;
    size_t len;

    if (buffer == NULL || length == NULL || buffer_size < 2) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    len = strcspn(buffer, "\r\n");

    if (buffer[len] == '\r' || buffer[len] == '\n') {
        char terminator = buffer[len];

        buffer[len] = '\0';

        if (terminator == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
            if (ch != '\n' && ch != EOF) {
                if (ungetc(ch, stdin) == EOF) {
                    return -1;
                }
            }
        }
    } else if (len == buffer_size - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch != '\n' && ch != '\r' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            return -1;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
            if (ch != '\n' && ch != EOF) {
                if (ungetc(ch, stdin) == EOF) {
                    return -1;
                }
            }
        }
    }

    *length = len;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_SIZE];
    size_t input_length;

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