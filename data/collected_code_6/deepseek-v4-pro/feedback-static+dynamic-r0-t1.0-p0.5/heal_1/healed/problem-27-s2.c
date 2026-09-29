#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char *remove_digits(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }
    
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    
    return result;
}

void remove_digits_from_list(char **list, size_t count) {
    if (list == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            char *cleaned = remove_digits(list[i]);
            if (cleaned != NULL) {
                free(list[i]);
                list[i] = cleaned;
            }
        }
    }
}

int main(void) {
    char *str1 = malloc(strlen("abc123def") + 1);
    char *str2 = malloc(strlen("456") + 1);
    char *str3 = malloc(strlen("hello") + 1);
    char *str4 = malloc(strlen("a1b2c3") + 1);
    
    if (str1 == NULL || str2 == NULL || str3 == NULL || str4 == NULL) {
        free(str1);
        free(str2);
        free(str3);
        free(str4);
        return 1;
    }
    
    strcpy(str1, "abc123def");
    strcpy(str2, "456");
    strcpy(str3, "hello");
    strcpy(str4, "a1b2c3");
    
    char *strings[] = {str1, str2, str3, str4};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    remove_digits_from_list(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    
    return 0;
}