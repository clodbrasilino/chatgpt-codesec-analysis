#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define DATE_LENGTH 10U
#define INPUT_SIZE (DATE_LENGTH + 2U)
#define OUTPUT_SIZE (DATE_LENGTH + 1U)

static int is_leap_year(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) ||
           (year % 400 == 0);
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

static int parse_digits(const char *text, size_t count, int *value)
{
    size_t i;
    int result = 0;

    if (text == NULL || value == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (text[i] < '0' || text[i] > '9') {
            return -1;
        }

        result = result * 10 + (text[i] - '0');
    }

    *value = result;
    return 0;
}

static int convert_date(const char *input, char *output, size_t output_size)
{
    int year;
    int month;
    int day;
    int result;

    if (input == NULL || output == NULL ||
        output_size < OUTPUT_SIZE ||
        strnlen(input, DATE_LENGTH + 1U) != DATE_LENGTH) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    if (parse_digits(input, 4U, &year) != 0 ||
        parse_digits(input + 5U, 2U, &month) != 0 ||
        parse_digits(input + 8U, 2U, &day) != 0) {
        return -1;
    }

    if (year < 1 ||
        month < 1 || month > 12 ||
        day < 1 || day > days_in_month(year, month)) {
        return -1;
    }

    result = snprintf(output, output_size, "%02d-%02d-%04d",
                      day, month, year);

    /* Possible weaknesses found:
     *  Assuming that condition 'result!=(int)10U' is not redundant
     */
    if (result != (int)DATE_LENGTH ||
        /* Possible weaknesses found:
         *  Condition 'result<0' is always false
         *  Condition 'result<0' is always false [knownConditionTrueFalse]
         */
        result < 0 ||
        (size_t)result >= output_size) {
        return -1;
    }

    return 0;
}

static int consume_line_ending(void)
{
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int ch = fgetc(stdin);

    if (ch == '\n' || ch == EOF) {
        return 0;
    }

    if (ch == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        return (ch == '\n' || ch == EOF) ? 0 : -1;
    }

    return -1;
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
    size_t length;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    length = strnlen(input, sizeof(input));

    if (length == sizeof(input)) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';

        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    } else {
        if (length != DATE_LENGTH || consume_line_ending() != 0) {
            fputs("Invalid date\n", stderr);
            return 1;
        }
    }

    if (length != DATE_LENGTH ||
        convert_date(input, output, sizeof(output)) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        return 1;
    }

    return 0;
}