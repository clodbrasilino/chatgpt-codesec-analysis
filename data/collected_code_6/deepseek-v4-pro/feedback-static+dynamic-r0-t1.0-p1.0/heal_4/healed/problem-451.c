#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_whitespaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);

    if (input_len == 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]", REG_EXTENDED);
    if (reti != 0) {
        return NULL;
    }

    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_index = 0;
    regmatch_t match;
    const char* cursor = input;
    int exec_result;

    while ((exec_result = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (result_index + copy_len > input_len) {
                copy_len = input_len - result_index;
            }
            if (copy_len > 0) {
                memcpy(result + result_index, cursor, copy_len);
                result_index += copy_len;
            }
        }

        cursor += match.rm_eo;

        if (match.rm_eo == 0) {
            if (*cursor != '\0') {
                if (result_index < input_len) {
                    result[result_index++] = *cursor;
                }
                cursor++;
            } else {
                break;
            }
        }
    }

    if (exec_result == REG_NOMATCH && *cursor != '\0') {
        size_t remaining = strlen(cursor);
        size_t available = input_len - result_index;
        size_t copy_len = (remaining < available) ? remaining : available;

        if (copy_len > 0 && result_index + copy_len <= input_len) {
            memcpy(result + result_index, cursor, copy_len);
            result_index += copy_len;
        }
    }

    if (result_index <= input_len) {
        result[result_index] = '\0';
    } else {
        result[input_len] = '\0';
    }

    regfree(&regex);
    return result;
}

int main() {
    const char* test_string = "Hello World\tfrom\nC programming";
    char* cleaned = remove_whitespaces(test_string);

    if (cleaned != NULL) {
        printf("Original: '%s'\n", test_string);
        printf("Cleaned: '%s'\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}