#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int length;
} Tuple;

char *concatenate(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    
    size_t len1 = strnlen(str1, 4096);
    size_t len2 = strnlen(str2, 4096);
    
    if (len1 > 4096 || len2 > 4096) {
        return NULL;
    }
    
    size_t total_len = len1 + len2;
    if (total_len < len1 || total_len > 8192) {
        return NULL;
    }
    
    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    if (len1 > 0) {
        memcpy(result, str1, len1);
    }
    if (len2 > 0) {
        memcpy(result + len1, str2, len2);
    }
    result[total_len] = '\0';
    
    return result;
}

Tuple *adjacent_concatenation(Tuple *input) {
    if (input == NULL || input->length <= 0 || input->items == NULL) {
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    if (input->length == 1) {
        result->length = 0;
        result->items = NULL;
        return result;
    }

    result->length = input->length - 1;
    result->items = (char **)calloc(result->length, sizeof(char *));
    if (result->items == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < result->length; i++) {
        if (input->items[i] == NULL || input->items[i + 1] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result->items[j]);
            }
            free(result->items);
            free(result);
            return NULL;
        }
        result->items[i] = concatenate(input->items[i], input->items[i + 1]);
        if (result->items[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result->items[j]);
            }
            free(result->items);
            free(result);
            return NULL;
        }
    }

    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (int i = 0; i < tuple->length; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

int main(void) {
    const char *data[] = {"ab", "cd", "ef", "gh"};
    int data_length = sizeof(data) / sizeof(data[0]);

    Tuple *input = (Tuple *)malloc(sizeof(Tuple));
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    input->length = data_length;
    input->items = (char **)calloc(data_length, sizeof(char *));
    if (input->items == NULL) {
        free(input);
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < data_length; i++) {
        size_t len = strnlen(data[i], 4096);
        if (len > 4096) {
            for (int j = 0; j < i; j++) {
                free(input->items[j]);
            }
            free(input->items);
            free(input);
            return EXIT_FAILURE;
        }
        input->items[i] = (char *)malloc(len + 1);
        if (input->items[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(input->items[j]);
            }
            free(input->items);
            free(input);
            return EXIT_FAILURE;
        }
        memcpy(input->items[i], data[i], len);
        input->items[i][len] = '\0';
    }

    Tuple *result = adjacent_concatenation(input);
    if (result == NULL) {
        free_tuple(input);
        return EXIT_FAILURE;
    }

    printf("Input tuple: ");
    for (int i = 0; i < input->length; i++) {
        printf("%s", input->items[i]);
        if (i < input->length - 1) {
            printf(", ");
        }
    }
    printf("\n");

    printf("Adjacent concatenations: ");
    for (int i = 0; i < result->length; i++) {
        printf("%s", result->items[i]);
        if (i < result->length - 1) {
            printf(", ");
        }
    }
    printf("\n");

    free_tuple(input);
    free_tuple(result);

    return EXIT_SUCCESS;
}