#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t result_len = 0;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = malloc(strlen(input) + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result + result_len, cursor);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result_len += strlen(cursor);
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        if (match.rm_so > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, (size_t)match.rm_so);
            result_len += (size_t)match.rm_so;
        }
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test = "Hello, World! 123 @#$% C-Programming_2024";
    char *cleaned = remove_non_alphanumeric(test);

    if (cleaned == NULL) {
        fprintf(stderr, "Error: string processing failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}