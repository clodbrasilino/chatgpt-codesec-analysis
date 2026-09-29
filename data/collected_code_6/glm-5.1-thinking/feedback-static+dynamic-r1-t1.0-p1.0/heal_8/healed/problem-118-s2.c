#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **string_to_list(const char *str, const char *delim) {
    if (str == NULL) {
        return NULL;
    }
    if (delim == NULL) {
        delim = " \t\n\r";
    }

    int delim_table[256] = {0};
    for (const char *d = delim; *d != '\0'; d++) {
        delim_table[(unsigned char)*d] = 1;
    }

    char **list = NULL;
    size_t capacity = 0;
    size_t count = 0;

    size_t i = 0;
    while (str[i] != '\0') {
        while (str[i] != '\0' && delim_table[(unsigned char)str[i]]) {
            i++;
        }
        if (str[i] == '\0') break;

        size_t start = i;
        while (str[i] != '\0' && !delim_table[(unsigned char)str[i]]) {
            i++;
        }

        size_t token_len = i - start;

        if (count >= capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
            char **new_list = realloc(list, (new_capacity + 1) * sizeof(char *));
            if (new_list == NULL) {
                for (size_t j = 0; j < count; j++) {
                    free(list[j]);
                }
                free(list);
                return NULL;
            }
            list = new_list;
            capacity = new_capacity;
        }

        char *token_copy = malloc(token_len + 1);
        if (token_copy == NULL) {
            for (size_t j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        memcpy(token_copy, str + start, token_len);
        token_copy[token_len] = '\0';
        list[count] = token_copy;

        count++;
    }

    if (count == 0) {
        list = malloc(sizeof(char *));
        if (list == NULL) {
            return NULL;
        }
    } else {
        char **new_list = realloc(list, (count + 1) * sizeof(char *));
        if (new_list != NULL) {
            list = new_list;
        }
    }

    list[count] = NULL;

    return list;
}

void free_list(char **list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    int buffer_size = 4096;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return 1;
    }
    while (fgets(buffer, buffer_size, stdin)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        char **list = string_to_list(buffer, " \t\n\r");
        if (list != NULL) {
            for (size_t i = 0; list[i] != NULL; i++) {
                printf("%s\n", list[i]);
            }
            free_list(list);
            fflush(stdout);
        }
    }
    free(buffer);
    return 0;
}