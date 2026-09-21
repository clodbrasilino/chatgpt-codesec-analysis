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
    size_t input_len;
    size_t output_len;
    char *output = NULL;
    char *temp = NULL;
    const char *search_ptr;
    size_t offset = 0;
    size_t remaining;
    size_t current_len;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, SIZE_MAX / 2);
    if (input_len >= SIZE_MAX / 2 - 1) {
        return NULL;
    }
    output_len = input_len * 2 + 1;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    output = (char *)malloc(output_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }
    output[0] = '\0';
    current_len = 0;
    search_ptr = input;

    while (regexec(&regex, search_ptr, 2, matches, 0) == 0) {
        size_t copy_len = (size_t)(matches[0].rm_so + 1);

        while (current_len + copy_len + 2 > output_len) {
            size_t new_len;
            if (output_len > SIZE_MAX / 2) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            new_len = output_len * 2;
            temp = (char *)realloc(output, new_len);
            if (temp == NULL) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            output = temp;
            output_len = new_len;
        }

        if (copy_len > 0 && current_len + copy_len <= output_len) {
            memcpy(output + current_len, search_ptr, copy_len);
            current_len += copy_len;
            output[current_len] = ' ';
            current_len++;
            output[current_len] = '\0';
        }

        offset += matches[0].rm_eo;
        search_ptr = input + offset;
    }

    remaining = strnlen(search_ptr, SIZE_MAX - current_len - 1);

    if (current_len > SIZE_MAX - remaining - 1) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    if (current_len + remaining + 1 > output_len) {
        size_t new_len = current_len + remaining + 1;
        temp = (char *)realloc(output, new_len);
        if (temp == NULL) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        output = temp;
        output_len = new_len;
    }

    memcpy(output + current_len, search_ptr, remaining + 1);
    current_len += remaining;
    output[current_len] = '\0';

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