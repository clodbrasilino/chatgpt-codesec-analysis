#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = safe_strlen(str, SIZE_MAX);
    if (len == 0) {
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
        size_t len = safe_strlen(source_strings[i], SIZE_MAX);
        size_t buf_size = len + 1;
        
        list[i] = malloc(buf_size);
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                if (list[j] != NULL) {
                    free(list[j]);
                    list[j] = NULL;
                }
            }
            free(list);
            return EXIT_FAILURE;
        }
        
        if (buf_size > 0) {
            list[i][buf_size - 1] = '\0';
            if (len > 0) {
                memcpy(list[i], source_strings[i], len);
            }
        }
    }

    reverse_strings(list, count);

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            printf("%s\n", list[i]);
        }
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            free(list[i]);
            list[i] = NULL;
        }
    }
    free(list);

    return EXIT_SUCCESS;
}