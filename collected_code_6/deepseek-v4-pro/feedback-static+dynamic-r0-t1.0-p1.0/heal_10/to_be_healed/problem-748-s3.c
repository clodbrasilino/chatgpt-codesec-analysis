#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *insert_spaces(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "([a-z])([A-Z])";
    int ret;
    char *output = NULL;
    char *temp = NULL;
    const char *search_ptr = input;
    size_t offset = 0;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len >= SIZE_MAX / 2) {
        return NULL;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t output_len = input_len * 2 + 1;
    output = (char *)malloc(output_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }
    output[0] = '\0';

    while (regexec(&regex, search_ptr, 2, matches, 0) == 0) {
        if (matches[0].rm_so < 0 || matches[0].rm_eo < 0) {
            break;
        }

        size_t copy_len = (size_t)matches[0].rm_so + 1;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t current_len = strlen(output);

        if (current_len >= SIZE_MAX - copy_len - 1) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        while (current_len + copy_len + 1 >= output_len) {
            size_t new_len = output_len * 2;
            if (new_len <= output_len) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            temp = (char *)realloc(output, new_len);
            if (temp == NULL) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            output = temp;
            output_len = new_len;
        }

        if (copy_len > output_len - current_len) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + current_len, search_ptr, copy_len);
        current_len += copy_len;

        if (current_len + 1 >= output_len) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        output[current_len] = ' ';
        current_len++;
        output[current_len] = '\0';

        offset += (size_t)matches[0].rm_eo;
        search_ptr = input + offset;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining = strlen(search_ptr);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t current_len = strlen(output);

    if (current_len >= SIZE_MAX - remaining - 1) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    if (remaining + 1 > output_len - current_len) {
        size_t new_len = current_len + remaining + 1;
        if (new_len <= current_len) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        temp = (char *)realloc(output, new_len);
        if (temp == NULL) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        output = temp;
        output_len = new_len;
    }

    if (current_len + remaining + 1 <= output_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + current_len, search_ptr, remaining);
        output[current_len + remaining] = '\0';
    } else {
        free(output);
        regfree(&regex);
        return NULL;
    }

    regfree(&regex);
    return output;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "ThisIsATestString",
        "noSpacesHere",
        "Already Spaced String",
        "MixtureOfUPPERAndlower",
        "",
        "A",
        "aB",
        "AB",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *result = insert_spaces(test_strings[i]);
        if (result != NULL) {
            printf("'%s' -> '%s'\n", test_strings[i], result);
            free(result);
        } else {
            printf("'%s' -> error\n", test_strings[i]);
        }
    }

    return 0;
}