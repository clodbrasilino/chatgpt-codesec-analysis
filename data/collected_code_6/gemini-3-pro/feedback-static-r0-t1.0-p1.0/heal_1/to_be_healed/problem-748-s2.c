#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t out_len = strlen(input) * 2 + 1;
    char* output = malloc(out_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* p = input;
    char* out_p = output;
    regmatch_t matches[3];

    while (regexec(&regex, p, 3, matches, 0) == 0) {
        size_t copy_len = matches[1].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(out_p, p, copy_len);
        out_p += copy_len;
        *out_p = ' ';
        out_p++;
        p += matches[2].rm_so;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(out_p, p);

    regfree(&regex);
    return output;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsCTesting";
    char* result = add_spaces(test_str);

    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}