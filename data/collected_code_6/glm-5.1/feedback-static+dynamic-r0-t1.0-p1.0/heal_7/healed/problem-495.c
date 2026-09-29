#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) return NULL;

    regex_t regex;
    int status;
    regmatch_t match;
    size_t input_len = 0;
    while (input[input_len] != '\0') input_len++;

    size_t result_capacity = input_len + 1;
    char *result = (char *)malloc(result_capacity);
    if (result == NULL) return NULL;
    size_t result_len = 0;

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return NULL;
    }

    const char *cursor = input;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so > 0) {
            size_t copy_len = match.rm_so;
            if (result_len + copy_len >= result_capacity) {
                size_t new_capacity = (result_capacity * 2) > (result_len + copy_len + 1) ? (result_capacity * 2) : (result_len + copy_len + 1);
                char *new_result = (char *)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            size_t available = result_capacity - result_len;
            if (copy_len > available) {
                copy_len = available;
            }
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
            result[result_len] = '\0';
        }
        cursor += match.rm_eo;
    }

    if (status == REG_NOMATCH) {
        size_t remaining_len = 0;
        while (cursor[remaining_len] != '\0') remaining_len++;
        if (remaining_len > 0) {
            if (result_len + remaining_len >= result_capacity) {
                size_t new_capacity = result_len + remaining_len + 1;
                char *new_result = (char *)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            size_t available = result_capacity - result_len;
            if (remaining_len > available) {
                remaining_len = available;
            }
            memcpy(result + result_len, cursor, remaining_len);
            result_len += remaining_len;
            result[result_len] = '\0';
        }
    } else {
        free(result);
        regfree(&regex);
        return NULL;
    }

    regfree(&regex);

    char *trimmed_result = (char *)realloc(result, result_len + 1);
    if (trimmed_result != NULL) {
        return trimmed_result;
    }

    return result;
}

int main(void) {
    const char *input_string = "HelloWorld123abcDEF456ghiJKL";
    char *output_string = remove_lowercase_substrings(input_string);

    if (output_string != NULL) {
        printf("Input: %s\n", input_string);
        printf("Output: %s\n", output_string);
        free(output_string);
    } else {
        printf("Memory allocation or regex error occurred.\n");
    }

    return 0;
}