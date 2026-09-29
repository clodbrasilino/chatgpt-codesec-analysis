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

static size_t safe_copy(char *dest, size_t dest_size, size_t dest_offset,
                        const char *src, size_t src_len) {
    size_t available = dest_size - dest_offset;
    if (available == 0) {
        return 0;
    }
    size_t copy_len = src_len < available ? src_len : available - 1;
    memcpy(dest + dest_offset, src, copy_len);
    return copy_len;
}

void remove_lowercase_substrings(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }

    output[0] = '\0';

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    size_t input_len = safe_strlen(input, output_size);
    if (input_len == 0) {
        regfree(&regex);
        return;
    }

    size_t in_pos = 0;
    size_t out_pos = 0;
    regmatch_t match;

    while (in_pos < input_len && out_pos < output_size - 1) {
        ret = regexec(&regex, input + in_pos, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - in_pos;
            size_t copied = safe_copy(output, output_size, out_pos,
                                      input + in_pos, remaining);
            out_pos += copied;
            break;
        } else if (ret == 0) {
            size_t match_start = match.rm_so;
            if (match_start > 0) {
                size_t copied = safe_copy(output, output_size, out_pos,
                                          input + in_pos, match_start);
                out_pos += copied;
                if (out_pos >= output_size - 1) {
                    break;
                }
            }
            size_t match_length = match.rm_eo;
            if (in_pos + match_length > input_len) {
                break;
            }
            in_pos += match_length;
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
    const char *test_str = "HelloWorld123abcDEFxyz456";
    char result[256];

    remove_lowercase_substrings(test_str, result, sizeof(result));
    printf("Original: %s\n", test_str);
    printf("Result: %s\n", result);

    return 0;
}