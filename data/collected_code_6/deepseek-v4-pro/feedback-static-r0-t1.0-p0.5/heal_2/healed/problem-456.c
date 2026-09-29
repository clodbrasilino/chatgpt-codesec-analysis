#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strnlen(str, 4096);
    if (len == 0) {
        return;
    }
    
    char *temp_str = strdup(str);
    if (temp_str == NULL) {
        return;
    }
    
    for (size_t i = 0; i < len; i++) {
        str[i] = temp_str[len - 1 - i];
    }
    
    free(temp_str);
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            reverse_string(strings[i]);
        }
    }
}

int main(void) {
    char data[][32] = {
        "hello",
        "world",
        "example",
        "test"
    };
    
    size_t count = sizeof(data) / sizeof(data[0]);
    
    char **strings = calloc(count + 1, sizeof(char *));
    if (strings == NULL) {
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        strings[i] = strndup(data[i], sizeof(data[i]) - 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
    }
    strings[count] = NULL;
    
    reverse_strings(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    
    free(strings);
    
    return 0;
}