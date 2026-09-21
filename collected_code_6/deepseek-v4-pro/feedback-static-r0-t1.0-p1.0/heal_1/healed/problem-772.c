#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_of_length(char* str, size_t str_size, int k) {
    if (str == NULL || str_size == 0 || k <= 0) {
        return str;
    }

    char* result = (char*)malloc(str_size);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    
    while (i < str_size && str[i] != '\0') {
        while (i < str_size && str[i] != '\0' && isspace((unsigned char)str[i])) {
            if (j < str_size - 1) {
                result[j++] = str[i];
            }
            i++;
        }

        if (i >= str_size || str[i] == '\0') break;

        size_t start = i;
        while (i < str_size && str[i] != '\0' && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_len = i - start;

        if (word_len != (size_t)k) {
            size_t w;
            for (w = start; w < i && j < str_size - 1; w++) {
                result[j++] = str[w];
            }
        }
    }

    if (j < str_size) {
        result[j] = '\0';
    } else {
        result[str_size - 1] = '\0';
    }

    size_t copy_len = j < str_size ? j + 1 : str_size;
    memmove(str, result, copy_len);
    free(result);
    return str;
}

int main(void) {
    char str[256];
    int k;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    str[strcspn(str, "\n")] = '\0';

    printf("Enter length k: ");
    if (scanf("%d", &k) != 1) {
        return 1;
    }

    remove_words_of_length(str, sizeof(str), k);
    printf("Result: \"%s\"\n", str);

    return 0;
}