#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_BUF_SIZE 11
#define YEAR_BUF_SIZE 5
#define MONTH_BUF_SIZE 3
#define DAY_BUF_SIZE 3

int convert_date(const char *input, char *output, size_t output_size);

static int copy_match(const char *input, size_t input_len,
                      const regmatch_t *match, char *dest, size_t dest_size,
                      size_t expected_len)
{
    size_t match_len;

    if (input == NULL || match == NULL || dest == NULL || dest_size == 0) {
        return -1;
    }

    if (match->rm_so < 0 || match->rm_eo < match->rm_so) {
        return -1;
    }

    if ((size_t)match->rm_eo > input_len) {
        return -1;
    }

    match_len = (size_t)(match->rm_eo - match->rm_so);

    if (match_len != expected_len || match_len >= dest_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, input + match->rm_so, match_len);
    dest[match_len] = '\0';

    return 0;
}

int convert_date(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t matches[4];
    int ret;
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year[YEAR_BUF_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUF_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day[DAY_BUF_SIZE];
    size_t input_len;

    if (input == NULL || output == NULL || output_size < DATE_BUF_SIZE) {
        return -1;
    }

    input_len = strnlen(input, DATE_BUF_SIZE);
    if (input_len != DATE_BUF_SIZE - 1) {
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

    if (copy_match(input, input_len, &matches[1], year, sizeof(year),
                   YEAR_BUF_SIZE - 1) != 0 ||
        copy_match(input, input_len, &matches[2], month, sizeof(month),
                   MONTH_BUF_SIZE - 1) != 0 ||
        copy_match(input, input_len, &matches[3], day, sizeof(day),
                   DAY_BUF_SIZE - 1) != 0) {
        regfree(&regex);
        return -1;
    }

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