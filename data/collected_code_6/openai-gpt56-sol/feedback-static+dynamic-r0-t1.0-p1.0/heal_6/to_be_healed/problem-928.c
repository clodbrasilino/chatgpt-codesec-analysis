#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define BUFFER_SIZE (DATE_LENGTH + 2U)

static int is_leap_year(unsigned int year)
{
    return year % 4U == 0U &&
           (year % 100U != 0U || year % 400U == 0U);
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch;
}

static int read_date(char *buffer, size_t buffer_size)
{
    size_t length;
    int ch;

    if (buffer == NULL || buffer_size < BUFFER_SIZE) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (buffer[length] == '\r') {
        buffer[length] = '\0';

        if (buffer[length + 1U] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
            if (ch != '\n' && ch != EOF) {
                discard_line();
                return -1;
            }
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        }

        if (ch != '\n' && ch != EOF) {
            discard_line();
            return -1;
        }
    }

    return length == DATE_LENGTH ? 0 : -1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int convert_date(const char input[static DATE_LENGTH + 1U],
                        /* Possible weaknesses found:
                         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                         */
                        char output[static DATE_LENGTH + 1U],
                        size_t output_size)
{
    static const unsigned int days_per_month[] = {
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int max_day;
    int written;
    size_t i;

    if (output_size < DATE_LENGTH + 1U) {
        return -1;
    }

    for (i = 0U; i < DATE_LENGTH; ++i) {
        if (i == 4U || i == 7U) {
            if (input[i] != '-') {
                return -1;
            }
        } else if (input[i] < '0' || input[i] > '9') {
            return -1;
        }
    }

    if (input[DATE_LENGTH] != '\0') {
        return -1;
    }

    year = (unsigned int)(input[0] - '0') * 1000U +
           (unsigned int)(input[1] - '0') * 100U +
           (unsigned int)(input[2] - '0') * 10U +
           (unsigned int)(input[3] - '0');

    month = (unsigned int)(input[5] - '0') * 10U +
            (unsigned int)(input[6] - '0');

    day = (unsigned int)(input[8] - '0') * 10U +
          (unsigned int)(input[9] - '0');

    if (year == 0U || month == 0U || month > 12U) {
        return -1;
    }

    max_day = days_per_month[month - 1U];

    if (month == 2U && is_leap_year(year)) {
        max_day = 29U;
    }

    if (day == 0U || day > max_day) {
        return -1;
    }

    written = snprintf(output, output_size, "%02u-%02u-%04u",
                       day, month, year);

    if (written != (int)DATE_LENGTH ||
        (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFFER_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[DATE_LENGTH + 1U] = {0};

    if (read_date(input, sizeof input) != 0 ||
        convert_date(input, output, sizeof output) != 0) {
        if (fputs("Invalid date\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (puts(output) == EOF) {
        return 1;
    }

    return 0;
}