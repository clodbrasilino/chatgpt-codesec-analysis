#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase(const char *input);

char *remove_lowercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t result_len;
    size_t input_len;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    result_len = 0;
    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(cursor);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, remaining);
            result_len += remaining;
            break;
        } else if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char errbuf[256];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            free(result);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, cursor, (size_t)match.rm_so);
        result_len += (size_t)match.rm_so;
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "HelloWorldFOO123bar",
        "KDeoALOklOOHserfLoAJSIskdsf",
        "ALLUPPERCASE",
        "alllowercase",
        "Mix3d C4s3 Str1ng"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_lowercase(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        printf("Original: %s\n", test_strings[i]);
        printf("Cleaned:  %s\n\n", cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}