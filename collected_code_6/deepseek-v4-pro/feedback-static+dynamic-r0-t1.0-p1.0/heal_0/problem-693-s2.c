#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]{2,}", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t alloc_size = input_len + 1;
    char *result = (char *)malloc(alloc_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t current_pos = 0;
    size_t result_pos = 0;
    regmatch_t match;

    while (current_pos <= input_len && regexec(&regex, input + current_pos, 1, &match, 0) == 0) {
        size_t prefix_len = match.rm_so;
        if (result_pos + prefix_len + 1 >= alloc_size) {
            alloc_size = (alloc_size * 2) + prefix_len + 2;
            char *temp = (char *)realloc(result, alloc_size);
            if (temp == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        memcpy(result + result_pos, input + current_pos, prefix_len);
        result_pos += prefix_len;

        result[result_pos] = ' ';
        result_pos++;

        current_pos += match.rm_eo;
    }

    if (current_pos < input_len) {
        size_t remaining_len = input_len - current_pos;
        if (result_pos + remaining_len + 1 >= alloc_size) {
            alloc_size = result_pos + remaining_len + 1;
            char *temp = (char *)realloc(result, alloc_size);
            if (temp == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }
        memcpy(result + result_pos, input + current_pos, remaining_len);
        result_pos += remaining_len;
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test1 = "This   is    a test   string.";
    const char *test2 = "  Leading   and   trailing   spaces  ";
    const char *test3 = "No multiple spaces here.";
    const char *test4 = "   ";
    const char *test5 = "";
    const char *test6 = "Tab\t\tand   spaces\n\nmixed";

    char *result = remove_multiple_spaces(test1);
    if (result != NULL) {
        printf("Test1: '%s' -> '%s'\n", test1, result);
        free(result);
    }

    result = remove_multiple_spaces(test2);
    if (result != NULL) {
        printf("Test2: '%s' -> '%s'\n", test2, result);
        free(result);
    }

    result = remove_multiple_spaces(test3);
    if (result != NULL) {
        printf("Test3: '%s' -> '%s'\n", test3, result);
        free(result);
    }

    result = remove_multiple_spaces(test4);
    if (result != NULL) {
        printf("Test4: '%s' -> '%s'\n", test4, result);
        free(result);
    }

    result = remove_multiple_spaces(test5);
    if (result != NULL) {
        printf("Test5: '%s' -> '%s'\n", test5, result);
        free(result);
    }

    result = remove_multiple_spaces(test6);
    if (result != NULL) {
        printf("Test6: '%s' -> '%s'\n", test6, result);
        free(result);
    }

    return 0;
}