#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    int size;
} Tuple;

char *concatenate(const char *a, const char *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    
    if (len_a > SIZE_MAX - len_b) {
        return NULL;
    }
    
    size_t total_len = len_a + len_b;
    if (total_len > SIZE_MAX - 1) {
        return NULL;
    }
    
    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    if (len_a > 0) {
        memcpy(result, a, len_a);
    }
    if (len_b > 0) {
        memcpy(result + len_a, b, len_b);
    }
    result[total_len] = '\0';
    
    return result;
}

Tuple *adjacent_concatenation(Tuple *input) {
    if (input == NULL || input->size < 2) {
        return NULL;
    }

    Tuple *output = (Tuple *)malloc(sizeof(Tuple));
    if (output == NULL) {
        return NULL;
    }

    output->size = input->size - 1;
    output->items = (char **)malloc(sizeof(char *) * output->size);
    if (output->items == NULL) {
        free(output);
        return NULL;
    }

    for (int i = 0; i < output->size; i++) {
        output->items[i] = concatenate(input->items[i], input->items[i + 1]);
        if (output->items[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(output->items[j]);
            }
            free(output->items);
            free(output);
            return NULL;
        }
    }

    return output;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (int i = 0; i < tuple->size; i++) {
            free(tuple->items[i]);
            tuple->items[i] = NULL;
        }
        free(tuple->items);
        tuple->items = NULL;
    }
    free(tuple);
}

int main(void) {
    const char *data[] = {"ab", "cd", "ef", "gh"};
    int data_size = (int)(sizeof(data) / sizeof(data[0]));

    Tuple input;
    input.size = data_size;
    input.items = (char **)malloc(sizeof(char *) * data_size);
    if (input.items == NULL) {
        return 1;
    }

    for (int i = 0; i < data_size; i++) {
        size_t len = strlen(data[i]);
        
        input.items[i] = (char *)malloc(len + 1);
        if (input.items[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(input.items[j]);
            }
            free(input.items);
            return 1;
        }
        
        memcpy(input.items[i], data[i], len);
        input.items[i][len] = '\0';
    }

    Tuple *result = adjacent_concatenation(&input);
    if (result == NULL) {
        for (int i = 0; i < input.size; i++) {
            free(input.items[i]);
        }
        free(input.items);
        return 1;
    }

    for (int i = 0; i < result->size; i++) {
        if (result->items[i] != NULL) {
            printf("%s\n", result->items[i]);
        }
    }

    for (int i = 0; i < input.size; i++) {
        free(input.items[i]);
    }
    free(input.items);
    free_tuple(result);

    return 0;
}