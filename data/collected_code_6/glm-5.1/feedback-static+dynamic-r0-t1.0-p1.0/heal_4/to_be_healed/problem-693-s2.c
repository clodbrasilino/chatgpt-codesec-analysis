#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (str[input_len] != '\0') {
        input_len++;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    const char *cursor = str;
    size_t result_index = 0;

    while (*cursor != '\0') {
        regmatch_t match;
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            if (match.rm_so > 0) {
                if (result_index + match.rm_so <= input_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_index, cursor, match.rm_so);
                    result_index += match.rm_so;
                }
            }

            if (result_index + 1 <= input_len) {
                result[result_index++] = ' ';
            }

            cursor += match.rm_eo;
        } else {
            const char *temp_cursor = cursor;
            while (*temp_cursor != '\0') {
                if (result_index + 1 <= input_len) {
                    result[result_index++] = *temp_cursor;
                }
                temp_cursor++;
            }
            break;
        }
    }

    result[result_index] = '\0';
    regfree(&regex);

    char *shrunk_result = (char *)realloc(result, result_index + 1);
    if (shrunk_result != NULL) {
        return shrunk_result;
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "Google  Assistant",
        "Quad   Core",
        "ChromeCast  Built-in",
        "This   is   a  test   string.",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *output = remove_multiple_spaces(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }
    
    return 0;
}