#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

char *remove_words_of_length_k(const char *input, size_t k)
{
    size_t len;
    size_t i;
    size_t out_pos;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    i = 0U;
    out_pos = 0U;
    while (i < len) {
        if (isspace((unsigned char)input[i])) {
            if (out_pos < len) {
                result[out_pos] = input[i];
                out_pos++;
            }
            i++;
        } else {
            size_t start = i;
            size_t word_len;
            while ((i < len) && (!isspace((unsigned char)input[i]))) {
                i++;
            }
            word_len = i - start;
            if (word_len != k) {
                if ((out_pos + word_len) <= len) {
                    memcpy(&result[out_pos], &input[start], word_len);
                    out_pos += word_len;
                } else {
                    free(result);
                    return NULL;
                }
            } else {
                if ((out_pos > 0U) && (result[out_pos - 1U] == ' ')) {
                    out_pos--;
                }
            }
        }
    }
    result[out_pos] = '\0';
    return result;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over a lazy dog";
    size_t k = 3U;
    char *cleaned;

    cleaned = remove_words_of_length_k(text, k);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", text) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }
    if (printf("Result:   %s\n", cleaned) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    free(cleaned);
    return EXIT_SUCCESS;
}