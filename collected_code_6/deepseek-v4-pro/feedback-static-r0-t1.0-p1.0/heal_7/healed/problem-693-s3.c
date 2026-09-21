#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        if (input_len == SIZE_MAX) {
            return NULL;
        }
        input_len++;
    }

    size_t max_output_len = input_len + 1;

    char *result = (char *)malloc(max_output_len);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < input_len) {
        if (isspace((unsigned char)input[src_pos])) {
            while (src_pos < input_len && isspace((unsigned char)input[src_pos])) {
                src_pos++;
            }

            if (dst_pos > 0 && src_pos < input_len) {
                if (dst_pos + 2 > max_output_len) {
                    size_t new_size = max_output_len * 2;
                    if (new_size <= max_output_len) {
                        free(result);
                        return NULL;
                    }
                    char *temp = (char *)realloc(result, new_size);
                    if (temp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    max_output_len = new_size;
                }
                result[dst_pos++] = ' ';
            }
        } else {
            size_t word_start = src_pos;
            while (src_pos < input_len && !isspace((unsigned char)input[src_pos])) {
                src_pos++;
            }

            size_t word_len = src_pos - word_start;
            while (dst_pos + word_len + 1 > max_output_len) {
                size_t new_size = max_output_len * 2 + word_len;
                if (new_size <= max_output_len) {
                    free(result);
                    return NULL;
                }
                char *temp = (char *)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                max_output_len = new_size;
            }

            memmove(result + dst_pos, input + word_start, word_len);
            dst_pos += word_len;
        }
    }

    if (dst_pos > 0 && result[dst_pos - 1] == ' ') {
        dst_pos--;
    }

    result[dst_pos] = '\0';

    {
        char *temp = (char *)realloc(result, dst_pos + 1);
        if (temp != NULL) {
            result = temp;
        }
    }

    return result;
}

int main(void) {
    const char *test_strings[] = {
        "Hello   World",
        "  Multiple   spaces   here  ",
        "NoSpaces",
        "",
        "   ",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *cleaned = remove_multiple_spaces(test_strings[i]);
        if (cleaned != NULL) {
            printf("Original: \"%s\"\n", test_strings[i]);
            printf("Cleaned:  \"%s\"\n\n", cleaned);
            free(cleaned);
        } else {
            printf("Error processing string %d\n", i);
        }
    }

    return 0;
}