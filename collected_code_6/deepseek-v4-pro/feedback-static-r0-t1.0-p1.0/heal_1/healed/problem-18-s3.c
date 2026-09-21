#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *remove_chars(char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return str1;
    }

    int table[256] = {0};
    size_t i, j = 0;
    size_t len1 = strnlen(str1, 4096);
    size_t len2 = strnlen(str2, 4096);

    for (i = 0; i < len2; i++) {
        table[(unsigned char)str2[i]] = 1;
    }

    for (i = 0; i < len1; i++) {
        if (!table[(unsigned char)str1[i]]) {
            str1[j++] = str1[i];
        }
    }

    str1[j] = '\0';
    return str1;
}

int main(void) {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;

    printf("Enter first string: ");
    if (getline(&str1, &size1, stdin) == -1) {
        free(str1);
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    if (getline(&str2, &size2, stdin) == -1) {
        free(str1);
        free(str2);
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    remove_chars(str1, str2);

    printf("Result: %s\n", str1);

    free(str1);
    free(str2);
    return 0;
}