#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char *resize_buffer(char *buffer, size_t *current_size, size_t required_size) {
    size_t new_size = *current_size;
    while (new_size <= required_size) {
        if (new_size > SIZE_MAX / 2) {
            free(buffer);
            return NULL;
        }
        new_size *= 2;
    }
    char *temp = (char *)realloc(buffer, new_size);
    if (temp == NULL) {
        free(buffer);
        return NULL;
    }
    *current_size = new_size;
    return temp;
}

char *remove_uppercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    if (len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'result_size=len+1', assigned value is greater than 0
     */
    size_t result_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'result_size==0' is always false [knownConditionTrueFalse]
     *  Condition 'result_size==0' is always false
     */
    if (result_size == 0) {
        regfree(&regex);
        return NULL;
    }

    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < len && regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
        size_t match_start = src_pos + match.rm_so;
        size_t match_end = src_pos + match.rm_eo;

        if (match_start > src_pos) {
            size_t copy_size = match_start - src_pos;
            if (copy_size > SIZE_MAX - dst_pos || dst_pos + copy_size + 1 > result_size) {
                size_t required = dst_pos + copy_size + 1;
                if (required < dst_pos) {
                    regfree(&regex);
                    free(result);
                    return NULL;
                }
                result = resize_buffer(result, &result_size, required);
                if (result == NULL) {
                    regfree(&regex);
                    return NULL;
                }
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, copy_size);
            dst_pos += copy_size;
        }

        src_pos = match_end;

        if (match.rm_eo == match.rm_so) {
            if (src_pos < len) {
                if (dst_pos + 2 > result_size) {
                    /* Possible weaknesses found:
                     *  required is assigned 'dst_pos+2' here.
                     */
                    size_t required = dst_pos + 2;
                    /* Possible weaknesses found:
                     *  Condition 'required<dst_pos' is always false [knownConditionTrueFalse]
                     *  Condition 'required<dst_pos' is always false
                     */
                    if (required < dst_pos) {
                        regfree(&regex);
                        free(result);
                        return NULL;
                    }
                    result = resize_buffer(result, &result_size, required);
                    if (result == NULL) {
                        regfree(&regex);
                        return NULL;
                    }
                }
                result[dst_pos++] = input[src_pos++];
            } else {
                break;
            }
        }
    }

    if (src_pos < len) {
        size_t remaining = len - src_pos;
        if (remaining > SIZE_MAX - dst_pos || dst_pos + remaining + 1 > result_size) {
            size_t required = dst_pos + remaining + 1;
            if (required < dst_pos) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            result = resize_buffer(result, &result_size, required);
            if (result == NULL) {
                regfree(&regex);
                return NULL;
            }
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, input + src_pos, remaining);
        dst_pos += remaining;
    }

    if (dst_pos + 1 > result_size) {
        /* Possible weaknesses found:
         *  required is assigned 'dst_pos+1' here.
         */
        size_t required = dst_pos + 1;
        /* Possible weaknesses found:
         *  Condition 'required<dst_pos' is always false [knownConditionTrueFalse]
         *  Condition 'required<dst_pos' is always false
         */
        if (required < dst_pos) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        result = resize_buffer(result, &result_size, required);
        if (result == NULL) {
            regfree(&regex);
            return NULL;
        }
    }

    result[dst_pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "HelloWORLDexampleTESTstring";
    char *cleaned = remove_uppercase_substrings(test_string);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}