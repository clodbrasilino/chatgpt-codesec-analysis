#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_OUT_LEN 11

int convert_date(const char *input, char *output, size_t output_size);

int convert_date(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t matches[4];
    int ret;
    size_t year_len;
    size_t month_len;
    size_t day_len;

    if (input == NULL || output == NULL || output_size < DATE_OUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, input, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    if (matches[1].rm_so < 0 || matches[2].rm_so < 0 || matches[3].rm_so < 0) {
        regfree(&regex);
        return -1;
    }

    year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

    if (year_len != 4 || month_len != 2 || day_len != 2) {
        regfree(&regex);
        return -1;
    }

    ret = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                   input + matches[3].rm_so,
                   input + matches[2].rm_so,
                   input + matches[1].rm_so);

    regfree(&regex);

    if (ret < 0 || (size_t)ret >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *input_date = "2024-05-17";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[DATE_OUT_LEN];

    memset(output_date, 0, sizeof(output_date));

    if (convert_date(input_date, output_date, sizeof(output_date)) != 0) {
        fprintf(stderr, "Failed to convert date: %s\n", input_date);
        return EXIT_FAILURE;
    }

    output_date[sizeof(output_date) - 1] = '\0';

    if (printf("Input: %s\nOutput: %s\n", input_date, output_date) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}