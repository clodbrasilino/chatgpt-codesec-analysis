#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_non_alphanumeric(const char* input, size_t input_len) {
    regex_t regex;
    regmatch_t match;
    char* result = NULL;
    size_t result_len = 0;
    size_t result_capacity = 0;
    const char* cursor = input;
    /* Possible weaknesses found:
     *  Null pointer addition
     *  Either the condition 'input==NULL' is redundant or there is pointer arithmetic with NULL pointer. [nullPointerArithmeticRedundantCheck]
     */
    const char* end = input + input_len;
    int ret;

    /* Possible weaknesses found:
     *  Assuming that condition 'input==NULL' is not redundant
     */
    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result_capacity = input_len + 1;
    result = (char*)malloc(result_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (cursor < end && *cursor != '\0') {
        size_t remaining = end - cursor;
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0) {
            if (match.rm_so < remaining && match.rm_eo <= remaining) {
                if (result_len + 1 >= result_capacity) {
                    size_t new_capacity = result_capacity * 2;
                    char* new_result = (char*)realloc(result, new_capacity);
                    if (new_result == NULL) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = new_result;
                    result_capacity = new_capacity;
                }
                result[result_len++] = cursor[match.rm_so];
                cursor += match.rm_eo;
            } else {
                break;
            }
        } else if (ret == REG_NOMATCH) {
            break;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_string = "Hello, World! 123 @#$";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test_len = strlen(test_string);
    char* cleaned = remove_non_alphanumeric(test_string, test_len);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}