#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_BUF_SIZE 11
#define YEAR_LEN 4
#define MONTH_LEN 2
#define DAY_LEN 2

int convert_date(const char *input, char *output, size_t output_size);

int convert_date(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t matches[4];
    int ret;
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year[YEAR_LEN + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_LEN + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day[DAY_LEN + 1];
    size_t year_len;
    size_t month_len;
    size_t day_len;

    if (input == NULL || output == NULL || output_size < DATE_BUF_SIZE) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
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

    if (year_len != YEAR_LEN || month_len != MONTH_LEN || day_len != DAY_LEN) {
        regfree(&regex);
        return -1;
    }

    if (year_len >= sizeof(year) || month_len >= sizeof(month) || day_len >= sizeof(day)) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year, input + matches[1].rm_so, year_len);
    year[year_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month, input + matches[2].rm_so, month_len);
    month[month_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day, input + matches[3].rm_so, day_len);
    day[day_len] = '\0';

    ret = snprintf(output, output_size, "%s-%s-%s", day, month, year);
    regfree(&regex);

    if (ret < 0 || (size_t)ret >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *input = "2024-05-17";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[DATE_BUF_SIZE];

    memset(output, 0, sizeof(output));

    if (convert_date(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Failed to convert date: %s\n", input);
        return EXIT_FAILURE;
    }

    if (printf("Input:  %s\nOutput: %s\n", input, output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}