#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_k_length_words(const char* str, int k) {
    if (str == NULL || k < 0) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (isalpha((unsigned char)str[i])) {
            size_t word_start = i;
            while (i < len && isalpha((unsigned char)str[i])) {
                i++;
            }
            size_t word_len = i - word_start;
            if (word_len != (size_t)k) {
                memcpy(result + res_idx, str + word_start, word_len);
                res_idx += word_len;
            }
        } else {
            result[res_idx++] = str[i++];
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    const char* input = argv[1];
    int k = atoi(argv[1]);

    if (k < 0) {
        fprintf(stderr, "k must be a non-negative integer\n");
        return 1;
    }

    char* output = remove_k_length_words(input, k);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return 1;
    }

    printf("%s\n", output);
    free(output);

    return 0;
}