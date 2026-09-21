#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *insert_spaces(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "([a-z])([A-Z])";
    int ret;
    size_t input_len;
    size_t output_len;
    char *output = NULL;
    char *temp = NULL;
    const char *search_ptr = input;
    size_t offset = 0;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);
    output_len = input_len + 1;

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

    while (regexec(&regex, search_ptr, 2, matches, 0) == 0) {
        size_t copy_len = matches[0].rm_so + 1;
        output_len += 1;
        temp = (char *)realloc(output, output_len);
        if (temp == NULL) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        output = temp;

        strncat(output, search_ptr, copy_len);
        output[strlen(output) + 1] = '\0';
        output[strlen(output)] = ' ';

        offset += matches[0].rm_eo;
        search_ptr = input + offset;
    }

    {
        size_t remaining = strlen(search_ptr);
        size_t current_len = strlen(output);
        output_len = current_len + remaining + 1;
        temp = (char *)realloc(output, output_len);
        if (temp == NULL) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        output = temp;
        memcpy(output + current_len, search_ptr, remaining + 1);
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