#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strlen(str);
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
    const size_t count = 4;
    const char *source_strings[] = {"hello", "reverse", "world", "string"};
    
    char **list = malloc(count * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        list[i] = NULL;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(source_strings[i]);
        size_t buf_size = len + 1;
        
        if (buf_size <= len) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        
        list[i] = malloc(buf_size);
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        
        if (buf_size <= len) {
            free(list[i]);
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        
        memcpy(list[i], source_strings[i], len);
        list[i][len] = '\0';
    }

    reverse_strings(list, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}