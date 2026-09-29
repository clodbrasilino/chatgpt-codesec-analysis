#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces_before_capitals(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z]";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len * 2 + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_pos = 0;
    size_t search_pos = 0;
    const char *current = input;

    while (search_pos <= input_len) {
        int match_result = regexec(&regex, current, 1, matches, 0);
        if (match_result != 0) {
            strcpy(result + result_pos, current);
            result_pos += strlen(current);
            break;
        }

        if (matches[0].rm_so > 0) {
            strncpy(result + result_pos, current, matches[0].rm_so);
            result_pos += matches[0].rm_so;
            result[result_pos++] = ' ';
        }

        result[result_pos++] = current[matches[0].rm_so];
        search_pos += matches[0].rm_so + 1;
        current += matches[0].rm_so + 1;
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "thisIsATest",
        "NoCapitals",
        "Already Spaced String",
        "ABC",
        "",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *result = add_spaces_before_capitals(test_strings[i]);
        if (result != NULL) {
            printf("Input: '%s'\nOutput: '%s'\n\n", test_strings[i], result);
            free(result);
        } else {
            printf("Input: '%s'\nOutput: (error)\n\n", test_strings[i]);
        }
    }

    return 0;
}