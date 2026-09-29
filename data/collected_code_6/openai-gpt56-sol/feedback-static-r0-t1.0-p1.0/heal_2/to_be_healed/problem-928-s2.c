#include <stdio.h>

#define DATE_LENGTH 10
#define BUFFER_SIZE (DATE_LENGTH + 1)

static int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

static int days_in_month(int year, int month)
{
    static const int days[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days[month - 1];
}

static int parse_digits(const char *text, size_t count)
{
    int value = 0;
    size_t i;

    for (i = 0; i < count; ++i) {
        if (text[i] < '0' || text[i] > '9') {
            return -1;
        }
        value = value * 10 + (text[i] - '0');
    }

    return value;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int convert_date(const char input[static BUFFER_SIZE],
                        /* Possible weaknesses found:
                         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                         */
                        char output[static BUFFER_SIZE],
                        size_t output_size)
{
    int year;
    int month;
    int day;
    int result;

    if (output_size < BUFFER_SIZE ||
        input[4] != '-' ||
        input[7] != '-' ||
        input[DATE_LENGTH] != '\0') {
        return -1;
    }

    year = parse_digits(input, 4);
    month = parse_digits(input + 5, 2);
    day = parse_digits(input + 8, 2);

    if (year < 1 || month < 1 || month > 12 ||
        day < 1 || day > days_in_month(year, month)) {
        return -1;
    }

    result = snprintf(output, output_size, "%02d-%02d-%04d",
                      day, month, year);

    if (result != DATE_LENGTH) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[BUFFER_SIZE];
    int ch;
    size_t length = 0;

    while (length < DATE_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == EOF || ch == '\n' || ch == '\r') {
            break;
        }

        input[length++] = (char)ch;
    }

    input[length] = '\0';

    if (length == DATE_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
            if (ch != '\n' && ch != EOF) {
                while (ch != '\n' && ch != EOF) {
                    /* Possible weaknesses found:
                     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = getchar();
                }
                fputs("Invalid date\n", stderr);
                return 1;
            }
        } else if (ch != '\n' && ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            }
            fputs("Invalid date\n", stderr);
            return 1;
        }
    }

    if (convert_date(input, output, sizeof(output)) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}