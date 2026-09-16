#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *remove_odd_chars(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    memmove(str, result, j + 1);
    free(result);

    return str;
}

int main(void) {
    char str[] = "abcdefghij";
    
    printf("Original string: %s\n", str);
    
    if (remove_odd_chars(str) != NULL) {
        printf("After removing odd characters: %s\n", str);
    } else {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    return 0;
}