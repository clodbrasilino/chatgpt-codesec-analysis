#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static size_t safe_memcpy(char *dest, size_t dest_size, const char *src, size_t src_len) {
    size_t copy_len = src_len;
    if (copy_len > dest_size) {
        copy_len = dest_size;
    }
    if (copy_len > 0 && dest != NULL && src != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, copy_len);
    }
    return copy_len;
}

void remove_lowercase_substrings(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    size_t out_pos = 0;
    const char *cursor = input;
    int result;

    /* Possible weaknesses found:
     *  Assuming that condition 'output_size==0' is not redundant
     */
    if (output_size == 0 || output == NULL || input == NULL) {
        return;
    }

    result = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result != 0) {
        /* Possible weaknesses found:
         *  Condition 'output_size>0' is always true [knownConditionTrueFalse]
         *  Condition 'output_size>0' is always true
         */
        if (output_size > 0) {
            output[0] = '\0';
        }
        return;
    }

    while (*cursor != '\0' && out_pos < output_size - 1) {
        result = regexec(&regex, cursor, 1, &match, 0);
        if (result == REG_NOMATCH) {
            size_t remaining = safe_strlen(cursor, output_size - out_pos - 1);
            if (remaining > 0) {
                size_t copied = safe_memcpy(output + out_pos, output_size - out_pos - 1, cursor, remaining);
                out_pos += copied;
            }
            break;
        } else if (result == 0) {
            if (match.rm_so >= 0 && (size_t)match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                size_t available = output_size - out_pos - 1;
                if (copy_len > available) {
                    copy_len = available;
                }
                if (copy_len > 0) {
                    size_t copied = safe_memcpy(output + out_pos, available, cursor, copy_len);
                    out_pos += copied;
                }
            }
            if (match.rm_eo > match.rm_so) {
                cursor += match.rm_eo;
            } else {
                cursor++;
            }
        } else {
            size_t remaining = safe_strlen(cursor, output_size - out_pos - 1);
            if (remaining > 0) {
                size_t copied = safe_memcpy(output + out_pos, output_size - out_pos - 1, cursor, remaining);
                out_pos += copied;
            }
            break;
        }
    }

    if (out_pos < output_size) {
        output[out_pos] = '\0';
    /* Possible weaknesses found:
     *  Condition 'output_size>0' is always true [knownConditionTrueFalse]
     *  Condition 'output_size>0' is always true
     */
    } else if (output_size > 0) {
        output[output_size - 1] = '\0';
    }

    regfree(&regex);
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "abcXYZdef",
        "ABC123low456",
        "test",
        "UPPERlowerUPPER",
        "A1b2C3d4",
        "",
        "alllowercase"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    char *result_buffer;
    size_t buffer_size = 256;

    result_buffer = (char *)calloc(buffer_size, sizeof(char));
    if (result_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < num_tests; i++) {
        remove_lowercase_substrings(test_strings[i], result_buffer, buffer_size);
        printf("Input: '%s' -> Output: '%s'\n", test_strings[i], result_buffer);
    }

    free(result_buffer);
    return 0;
}