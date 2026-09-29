#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

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

    size_t result_size = 256;
    while (result_size <= len) {
        if (result_size > SIZE_MAX / 2) {
            regfree(&regex);
            return NULL;
        }
        result_size *= 2;
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

        /* Possible weaknesses found:
         *  Assuming that condition 'match_start>src_pos' is not redundant
         */
        if (match_start > src_pos) {
            /* Possible weaknesses found:
             *  Assignment 'copy_size=match_start-src_pos', assigned value is greater than 0
             */
            size_t copy_size = match_start - src_pos;
            if (dst_pos + copy_size >= result_size) {
                size_t required = dst_pos + copy_size + 1;
                result = resize_buffer(result, &result_size, required);
                if (result == NULL) {
                    regfree(&regex);
                    return NULL;
                }
            }
            /* Possible weaknesses found:
             *  Condition 'copy_size>0' is always true [knownConditionTrueFalse]
             *  Condition 'copy_size>0' is always true
             */
            if (copy_size > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, input + src_pos, copy_size);
                dst_pos += copy_size;
            }
        }

        src_pos = match_end;

        if (match.rm_eo == match.rm_so) {
            if (src_pos < len) {
                if (dst_pos + 1 >= result_size) {
                    size_t required = dst_pos + 2;
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

    /* Possible weaknesses found:
     *  Assuming that condition 'src_pos<len' is not redundant
     */
    if (src_pos < len) {
        /* Possible weaknesses found:
         *  Assignment 'remaining=len-src_pos', assigned value is greater than 0
         */
        size_t remaining = len - src_pos;
        if (dst_pos + remaining >= result_size) {
            size_t required = dst_pos + remaining + 1;
            result = resize_buffer(result, &result_size, required);
            if (result == NULL) {
                regfree(&regex);
                return NULL;
            }
        }
        /* Possible weaknesses found:
         *  Condition 'remaining>0' is always true
         *  Condition 'remaining>0' is always true [knownConditionTrueFalse]
         */
        if (remaining > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
        }
    }

    if (dst_pos >= result_size) {
        size_t required = dst_pos + 1;
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