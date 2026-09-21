#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define INPUT_SIZE (DATE_LENGTH + 2U)
#define OUTPUT_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(int year)
{
    return (year % 4 == 0) &&
           ((year % 100 != 0) || (year % 400 == 0));
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
static int convert_date(const char input[static DATE_LENGTH + 1U],
                        /* Possible weaknesses found:
                         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                         */
                        char output[static OUTPUT_SIZE])
{
    int year;
    int month;
    int day;
    int written;
    size_t i;

    output[0] = '\0';

    if (input[DATE_LENGTH] != '\0' ||
        input[4] != '-' ||
        input[7] != '-') {
        return -1;
    }

    for (i = 0U; i < DATE_LENGTH; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    year = (input[0] - '0') * 1000 +
           (input[1] - '0') * 100 +
           (input[2] - '0') * 10 +
           (input[3] - '0');

    month = (input[5] - '0') * 10 +
            (input[6] - '0');

    day = (input[8] - '0') * 10 +
          (input[9] - '0');

    if (year < 1 ||
        month < 1 || month > 12 ||
        day < 1 || day > days_in_month(year, month)) {
        return -1;
    }

    written = snprintf(output, OUTPUT_SIZE, "%02d-%02d-%04d",
                       day, month, year);

    if (written != (int)DATE_LENGTH) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == '\n') {
            return 0;
        }

        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    }
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int read_date(char buffer[static INPUT_SIZE])
{
    size_t length;
    int next;

    buffer[0] = '\0';

    if (fgets(buffer, (int)INPUT_SIZE, stdin) == NULL) {
        return -1;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\r') {
        if (buffer[length + 1U] == '\n') {
            buffer[length] = '\0';
        } else {
            buffer[length] = '\0';
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            next = getchar();

            if (next != '\n' && next != EOF) {
                if (discard_line() != 0) {
                    buffer[0] = '\0';
                    return -1;
                }
            }

            if (next == EOF && ferror(stdin)) {
                buffer[0] = '\0';
                return -1;
            }
        }
    } else if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        next = getchar();

        if (next != '\n' && next != EOF) {
            if (discard_line() != 0) {
                buffer[0] = '\0';
                return -1;
            }

            buffer[0] = '\0';
            return -1;
        }

        if (next == EOF && ferror(stdin)) {
            buffer[0] = '\0';
            return -1;
        }
    }

    if (length != DATE_LENGTH) {
        buffer[0] = '\0';
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_SIZE] = {0};

    if (read_date(input) != 0 ||
        convert_date(input, output) != 0) {
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