#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

char *add_spaces_before_capitals(const char *input)
{
    regex_t regex;
    regmatch_t match[3];
    const char *pattern = "\\([a-z]\\)\\([A-Z]\\)";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[256];
    size_t input_len;
    size_t capacity;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'prefix_len' can be reduced. [variableScope]
     */
    size_t prefix_len;
    char *result;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    if (input_len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return NULL;
    }

    capacity = input_len * 2 + 1;
    result = malloc(capacity);
    if (result == NULL) {
        fprintf(stderr, "malloc failed\n");
        regfree(&regex);
        return NULL;
    }

    length = 0;
    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 3, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            free(result);
            regfree(&regex);
            return NULL;
        }

        prefix_len = (size_t)match[1].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + length, cursor, prefix_len);
        length += prefix_len;
        result[length] = ' ';
        length++;
        cursor += prefix_len;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result + length, cursor);

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "HelloWorldThisIsARegexExample";
    char *output;

    output = add_spaces_before_capitals(input);
    if (output == NULL) {
        fprintf(stderr, "Failed to process input string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}