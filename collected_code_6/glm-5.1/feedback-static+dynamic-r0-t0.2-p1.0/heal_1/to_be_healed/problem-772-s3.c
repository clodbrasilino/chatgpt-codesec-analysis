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

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            size_t word_start = i;
            size_t word_len = 0;

            while (str[i] != '\0' && isalpha((unsigned char)str[i])) {
                word_len++;
                i++;
            }

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    int k = atoi(argv[2]);
    if (k < 0) {
        fprintf(stderr, "Error: k must be a non-negative integer.\n");
        return 1;
    }

    char* modified_str = remove_k_length_words(argv[1], k);
    if (modified_str == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return 1;
    }

    printf("%s\n", modified_str);

    free(modified_str);
    modified_str = NULL;

    return 0;
}