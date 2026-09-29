#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_of_length(char* str, int k) {
    if (str == NULL || k <= 0) {
        return str;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    
    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            result[j++] = str[i++];
        }

        size_t start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_len = i - start;

        if (word_len != (size_t)k) {
            size_t w;
            for (w = start; w < i; w++) {
                result[j++] = str[w];
            }
        }
    }

    result[j] = '\0';
    
    if (j >= len + 1) {
        free(result);
        return str;
    }
    
    memmove(str, result, j + 1);
    free(result);
    return str;
}

int main(void) {
    char* str = NULL;
    size_t buffer_size = 1024;
    int k;

    str = (char*)malloc(buffer_size);
    if (str == NULL) {
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(str, (int)buffer_size, stdin) == NULL) {
        free(str);
        return 1;
    }
    str[strcspn(str, "\n")] = '\0';

    printf("Enter length k: ");
    if (scanf("%d", &k) != 1) {
        free(str);
        return 1;
    }

    remove_words_of_length(str, k);
    printf("Result: \"%s\"\n", str);

    free(str);
    return 0;
}