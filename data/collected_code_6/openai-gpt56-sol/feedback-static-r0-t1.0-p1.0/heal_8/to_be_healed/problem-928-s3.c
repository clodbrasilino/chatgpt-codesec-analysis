#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define DATE_LENGTH 10U
#define INPUT_SIZE (DATE_LENGTH + 2U)
#define OUTPUT_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(unsigned int year)
{
    return ((year % 4U == 0U) && (year % 100U != 0U)) ||
           (year % 400U == 0U);
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int read_date(char *buffer, size_t buffer_size)
{
    size_t length;

    if (buffer == NULL || buffer_size < INPUT_SIZE ||
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        buffer_size > (size_t)INT_MAX) {
        return -1;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    length = strnlen(buffer, buffer_size);

    if (length == buffer_size) {
        buffer[0] = '\0';
        return -1;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';

        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[--length] = '\0';
        }
    } else if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[--length] = '\0';
    } else if (!feof(stdin)) {
        if (discard_line() != 0) {
            buffer[0] = '\0';
            return -1;
        }

        buffer[0] = '\0';
        return -1;
    }

    if (length != DATE_LENGTH) {
        buffer[0] = '\0';
        return -1;
    }

    return 0;
}

static int convert_date(const char *input, size_t input_size,
                        char *output, size_t output_size)
{
    static const unsigned int days_per_month[12] = {
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int max_day;
    size_t i;
    int written;

    if (input == NULL || output == NULL ||
        input_size < DATE_LENGTH + 1U ||
        output_size < OUTPUT_SIZE ||
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         */
        output_size > (size_t)INT_MAX) {
        return -1;
    }

    output[0] = '\0';

    if (strnlen(input, input_size) != DATE_LENGTH ||
        input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (i = 0U; i < DATE_LENGTH; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
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

    if (written < 0 || written != (int)DATE_LENGTH ||
        (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE] = { 0 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_SIZE] = { 0 };

    if (read_date(input, sizeof input) != 0) {
        fputs("Failed to read a valid date.\n", stderr);
        return 1;
    }

    if (convert_date(input, sizeof input, output, sizeof output) != 0) {
        fputs("Invalid date. Expected yyyy-mm-dd.\n", stderr);
        return 1;
    }

    if (puts(output) == EOF) {
        fputs("Failed to write the converted date.\n", stderr);
        return 1;
    }

    return 0;
}