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
    if (dest_offset >= dest_size) {
        return 0;
    }
    
    size_t available = dest_size - dest_offset;
    if (available <= 1) {
        return 0;
    }
    
    if (src == NULL || dest == NULL) {
        return 0;
    }
    
    size_t max_copy = available - 1;
    size_t copy_len = (src_len < max_copy) ? src_len : max_copy;
    
    if (copy_len > 0) {
        memcpy(dest + dest_offset, src, copy_len);
    }
    
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

    size_t input_len = strnlen(input, output_size);
    if (input_len == 0) {
        regfree(&regex);
        return;
    }

    size_t in_pos = 0;
    size_t out_pos = 0;
    regmatch_t match;

    while (in_pos < input_len && out_pos + 1 < output_size) {
        ret = regexec(&regex, input + in_pos, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - in_pos;
            size_t space_left = output_size - out_pos;
            if (remaining >= space_left) {
                remaining = space_left - 1;
            }
            size_t copied = safe_copy(output, output_size, out_pos,
                                      input + in_pos, remaining);
            out_pos += copied;
            break;
        } else if (ret == 0) {
            if (match.rm_so < 0 || match.rm_eo < 0) {
                break;
            }
            
            size_t match_start = (size_t)match.rm_so;
            size_t match_end = (size_t)match.rm_eo;
            
            if (match_start >= match_end) {
                break;
            }
            
            if (match_start > 0) {
                size_t prefix_len = match_start;
                size_t space_left = output_size - out_pos;
                if (prefix_len >= space_left) {
                    prefix_len = space_left - 1;
                }
                size_t copied = safe_copy(output, output_size, out_pos,
                                          input + in_pos, prefix_len);
                out_pos += copied;
                if (out_pos + 1 >= output_size) {
                    break;
                }
            }
            
            size_t match_length = match_end;
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
    char *result = calloc(256, sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    remove_lowercase_substrings(test_str, result, 256);
    printf("Original: %s\n", test_str);
    printf("Result: %s\n", result);

    free(result);
    return 0;
}