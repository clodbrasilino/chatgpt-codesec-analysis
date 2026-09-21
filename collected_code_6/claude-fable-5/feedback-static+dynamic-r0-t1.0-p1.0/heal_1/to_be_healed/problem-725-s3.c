#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *extract_quoted_value(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    char *result = NULL;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return NULL;
    }

    ret = regexec(&regex, input, 2, matches, 0);
    if (ret == 0) {
        if (matches[1].rm_so != -1 && matches[1].rm_eo >= matches[1].rm_so) {
            size_t len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
            result = malloc(len + 1);
            if (result != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, input + matches[1].rm_so, len);
                result[len] = '\0';
            } else {
                fprintf(stderr, "Memory allocation failed\n");
            }
        }
    } else if (ret != REG_NOMATCH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex execution failed: %s\n", errbuf);
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_string = "The value is \"hello world\" in this string";
    char *value;

    value = extract_quoted_value(test_string);
    if (value != NULL) {
        printf("Extracted value: %s\n", value);
        free(value);
    } else {
        printf("No quoted value found\n");
    }

    return EXIT_SUCCESS;
}