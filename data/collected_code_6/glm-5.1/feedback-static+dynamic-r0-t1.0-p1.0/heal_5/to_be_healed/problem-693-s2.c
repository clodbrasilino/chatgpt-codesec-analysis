#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(str);

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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining_len = strlen(cursor);
            if (result_index + remaining_len <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_index, cursor, remaining_len);
                result_index += remaining_len;
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