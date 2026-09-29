#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strnlen(str, 1024);
    if (len == 1024) {
        return;
    }
    
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i]);
    }
}

int main(void) {
    char *strings[] = {
        "hello",
        "world",
        "example",
        "test",
        NULL
    };
    
    size_t count = 0;
    while (strings[count] != NULL) {
        count++;
    }
    
    char **mutable_strings = malloc(count * sizeof(char *));
    if (mutable_strings == NULL) {
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        size_t len = strnlen(strings[i], 1024);
        if (len == 1024) {
            free(mutable_strings);
            return 1;
        }
        mutable_strings[i] = malloc(len + 1);
        if (mutable_strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(mutable_strings[j]);
            }
            free(mutable_strings);
            return 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(mutable_strings[i], strings[i], len + 1);
    }
    
    reverse_strings(mutable_strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", mutable_strings[i]);
        free(mutable_strings[i]);
    }
    
    free(mutable_strings);
    
    return 0;
}