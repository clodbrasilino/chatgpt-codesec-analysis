#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_chars(char *str1, const char *str2) {
    int table[256] = {0};
    int i, j = 0;
    
    if (str1 == NULL || str2 == NULL) {
        return str1;
    }
    
    for (i = 0; str2[i] != '\0'; i++) {
        table[(unsigned char)str2[i]] = 1;
    }
    
    for (i = 0; str1[i] != '\0'; i++) {
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
    size_t size1 = 100;
    size_t size2 = 100;
    
    str1 = malloc(size1);
    str2 = malloc(size2);
    
    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 1;
    }
    
    printf("Enter first string: ");
    if (fgets(str1, size1, stdin) == NULL) {
        free(str1);
        free(str2);
        return 1;
    }
    
    size_t len1 = strlen(str1);
    while (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }
    
    printf("Enter second string: ");
    if (fgets(str2, size2, stdin) == NULL) {
        free(str1);
        free(str2);
        return 1;
    }
    
    size_t len2 = strlen(str2);
    while (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }
    
    remove_chars(str1, str2);
    printf("Result: %s\n", str1);
    
    free(str1);
    free(str2);
    
    return 0;
}