#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_of_length_k(const char* str, int k) {
    if (str == NULL || k <= 0) {
        char* result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            size_t word_start = i;
            while (isalpha((unsigned char)str[i])) {
                i++;
            }
            size_t word_len = i - word_start;

            if (word_len != (size_t)k) {
                memcpy(result + j, str + word_start, word_len);
                j += word_len;
            }
        } else {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    const char* input = argv[1];
    int k = atoi(argv[1]);

    if (k <= 0) {
        fprintf(stderr, "Error: k must be a positive integer.\n");
        return 1;
    }

    char* output = remove_words_of_length_k(input, k);
    if (output == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    printf("%s\n", output);
    free(output);

    return 0;
}