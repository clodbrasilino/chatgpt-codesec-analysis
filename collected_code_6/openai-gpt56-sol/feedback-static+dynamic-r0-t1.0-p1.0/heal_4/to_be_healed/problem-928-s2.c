#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define BUFFER_SIZE (DATE_LENGTH + 1U)

static int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int convert_date(const char input[static BUFFER_SIZE],
                        /* Possible weaknesses found:
                         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                         */
                        char output[static BUFFER_SIZE])
{
    int year;
    int month;
    int day;
    int written;

    if (input[DATE_LENGTH] != '\0') {
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

    if (year < 1 || month < 1 || month > 12 ||
        day < 1 || day > days_in_month(year, month)) {
        return -1;
    }

    written = snprintf(output, BUFFER_SIZE, "%02d-%02d-%04d",
                       day, month, year);

    if (written != (int)DATE_LENGTH) {
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
    size_t length = 0U;
    int too_long = 0;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                too_long = 1;
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                while ((next = getchar()) != '\n' && next != EOF) {
                }
            }
            break;
        }

        if (length < DATE_LENGTH) {
            input[length++] = (char)ch;
        } else {
            too_long = 1;
        }
    }

    if (ferror(stdin) || (ch == EOF && length == 0U) ||
        too_long || length != DATE_LENGTH) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    input[length] = '\0';

    if (convert_date(input, output) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}