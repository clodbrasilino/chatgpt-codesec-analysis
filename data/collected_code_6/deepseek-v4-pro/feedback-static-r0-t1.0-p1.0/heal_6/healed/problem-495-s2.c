#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static size_t safe_memcpy(char *dest, size_t dest_size, const char *src, size_t src_len) {
    if (dest == NULL || src == NULL || dest_size == 0 || src_len == 0) {
        return 0;
    }
    size_t copy_len = src_len;
    if (copy_len >= dest_size) {
        copy_len = dest_size - 1;
    }
    if (copy_len > 0) {
        memmove(dest, src, copy_len);
    }
    return copy_len;
}

void remove_lowercase_substrings(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    size_t out_pos = 0;
    const char *cursor = input;
    int result;

    if (output_size == 0 || output == NULL || input == NULL) {
        return;
    }

    output[0] = '\0';

    result = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (result != 0) {
        return;
    }

    while (*cursor != '\0' && out_pos + 1 < output_size) {
        result = regexec(&regex, cursor, 1, &match, 0);
        if (result == REG_NOMATCH) {
            size_t available = output_size - out_pos;
            size_t remaining = safe_strlen(cursor, available - 1);
            if (remaining > 0) {
                size_t copied = safe_memcpy(output + out_pos, available, cursor, remaining);
                out_pos += copied;
            }
            break;
        } else if (result == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                size_t available = output_size - out_pos;
                if (copy_len >= available) {
                    copy_len = available - 1;
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
            break;
        }
    }

    if (out_pos < output_size) {
        output[out_pos] = '\0';
    } else {
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