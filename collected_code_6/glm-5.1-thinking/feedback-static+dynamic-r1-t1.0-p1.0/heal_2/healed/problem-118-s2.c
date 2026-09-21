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

    size_t tmp_len = strlen(str) + 1;
    char *tmp = malloc(tmp_len);
    if (tmp == NULL) {
        return NULL;
    }
    strncpy(tmp, str, tmp_len);
    tmp[tmp_len - 1] = '\0';

    char **list = NULL;
    size_t capacity = 0;
    size_t count = 0;

    char *token = strtok(tmp, delim);
    while (token != NULL) {
        if (count >= capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
            char **new_list = realloc(list, (new_capacity + 1) * sizeof(char *));
            if (new_list == NULL) {
                free(tmp);
                for (size_t i = 0; i < count; i++) {
                    free(list[i]);
                }
                free(list);
                return NULL;
            }
            list = new_list;
            capacity = new_capacity;
        }

        size_t token_len = strlen(token) + 1;
        list[count] = malloc(token_len);
        if (list[count] == NULL) {
            free(tmp);
            for (size_t i = 0; i < count; i++) {
                free(list[i]);
            }
            free(list);
            return NULL;
        }
        strncpy(list[count], token, token_len);
        list[count][token_len - 1] = '\0';

        count++;
        token = strtok(NULL, delim);
    }

    free(tmp);

    char **new_list = realloc(list, (count + 1) * sizeof(char *));
    if (new_list != NULL) {
        list = new_list;
    } else if (count == 0) {
        return NULL;
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
    const char *input = "hello world this is a test";
    const char *delim = " ";
    char **list = string_to_list(input, delim);
    
    if (list != NULL) {
        for (size_t i = 0; list[i] != NULL; i++) {
            printf("%s\n", list[i]);
        }
        free_list(list);
    }
    
    return 0;
}