#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input);
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char *remove_multiple_spaces(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    const char *cursor;
    size_t out_len;
    size_t buf_len;
    size_t remainder_len;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    buf_len = strlen(input) + 1U;
    output = malloc(buf_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    out_len = 0U;
    cursor = input;

    while ((ret = regexec(&regex, cursor, 1U, &match, 0)) == 0) {
        const size_t prefix_len = (size_t)match.rm_so;

        if ((out_len + prefix_len + 1U) >= buf_len) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + out_len, cursor, prefix_len);
        out_len += prefix_len;
        output[out_len] = ' ';
        out_len += 1U;
        cursor += match.rm_eo;
    }

    if (ret != REG_NOMATCH) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remainder_len = strlen(cursor);
    if ((out_len + remainder_len) >= buf_len) {
        free(output);
        regfree(&regex);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + out_len, cursor, remainder_len);
    out_len += remainder_len;
    output[out_len] = '\0';

    regfree(&regex);
    return output;
}

int main(void)
{
    const char *test = "This   is  a    string   with     multiple spaces.";
    char *result;

    result = remove_multiple_spaces(test);
    if (result == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    if (printf("Cleaned:  %s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}