#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_digits(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
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
    
    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        return shrunk;
    }
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
    const char *init_strings[] = {
        "abc123def",
        "456",
        "no digits here",
        "a1b2c3d4e5"
    };
    
    size_t count = sizeof(init_strings) / sizeof(init_strings[0]);
    
    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < count; i++) {
        strings[i] = NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        size_t needed = strnlen(init_strings[i], SIZE_MAX) + 1;
        strings[i] = malloc(needed);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        snprintf(strings[i], needed, "%s", init_strings[i]);
    }
    
    remove_digits_from_list(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    free(strings);
    
    return EXIT_SUCCESS;
}