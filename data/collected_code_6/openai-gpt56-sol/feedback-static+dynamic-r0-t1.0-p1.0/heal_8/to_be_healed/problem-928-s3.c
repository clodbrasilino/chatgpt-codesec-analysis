#include <limits.h>
#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10U
#define INPUT_BUFFER_SIZE (DATE_LENGTH + 2U)
#define OUTPUT_BUFFER_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(unsigned int year)
{
    return year % 4U == 0U &&
           (year % 100U != 0U || year % 400U == 0U);
}

static int convert_date(const char *input, size_t input_size,
                        char *output, size_t output_size)
{
    static const unsigned int days_per_month[] = {
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int maximum_day;
    size_t i;
    int written;

    if (input == NULL || output == NULL ||
        input_size < DATE_LENGTH + 1U ||
        output_size < OUTPUT_BUFFER_SIZE) {
        return -1;
    }

    output[0] = '\0';

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

    maximum_day = days_per_month[month - 1U];

    if (month == 2U && is_leap_year(year)) {
        maximum_day = 29U;
    }

    if (day == 0U || day > maximum_day) {
        return -1;
    }

    written = snprintf(output, output_size, "%02u-%02u-%04u",
                       day, month, year);

    if (written < 0 ||
        (size_t)written != DATE_LENGTH ||
        (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard[128];

    while (fgets(discard, sizeof discard, stdin) != NULL) {
        if (strchr(discard, '\n') != NULL) {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_date(char *buffer, size_t buffer_size)
{
    size_t length;

    if (buffer == NULL ||
        buffer_size < INPUT_BUFFER_SIZE ||
        buffer_size > (size_t)INT_MAX) {
        return -1;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    if (buffer[length] == '\r') {
        buffer[length] = '\0';

        if (discard_line() != 0) {
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        return strlen(buffer) == DATE_LENGTH ? 0 : -2;
    }

    if (length < buffer_size - 1U) {
        return 0;
    }

    if (discard_line() != 0) {
        return -1;
    }

    return -2;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_BUFFER_SIZE] = {0};
    int status;

    status = read_date(input, sizeof input);

    if (status == -1) {
        fputs("Failed to read the date.\n", stderr);
        return 1;
    }

    if (status != 0 ||
        convert_date(input, sizeof input, output, sizeof output) != 0) {
        fputs("Invalid date. Expected yyyy-mm-dd.\n", stderr);
        return 1;
    }

    if (fputs(output, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        return 1;
    }

    return 0;
}