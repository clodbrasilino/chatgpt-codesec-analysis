#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

static void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    tuple->items = NULL;
    tuple->count = 0;
}

static char *trim_whitespace(char *str, size_t *len) {
    char *end;
    size_t current_len;
    
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    if (*str == '\0') {
        *len = 0;
        return str;
    }
    
    current_len = strnlen(str, *len + 1);
    end = str + current_len - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    end[1] = '\0';
    *len = (size_t)(end - str) + 1;
    
    return str;
}

int string_to_tuple(const char *input, size_t input_len, Tuple *result) {
    char *buffer;
    char *token;
    char *saveptr;
    char **temp_items;
    size_t capacity = 10;
    size_t count = 0;
    size_t token_len;
    
    if (input == NULL || result == NULL) {
        return -1;
    }
    
    result->items = NULL;
    result->count = 0;
    
    buffer = malloc(input_len + 1);
    if (buffer == NULL) {
        return -1;
    }
    if (input_len > 0) {
        memcpy(buffer, input, input_len);
    }
    buffer[input_len] = '\0';
    
    temp_items = malloc(capacity * sizeof(char *));
    if (temp_items == NULL) {
        free(buffer);
        return -1;
    }
    
    token = strtok_r(buffer, ",", &saveptr);
    while (token != NULL) {
        char *trimmed;
        size_t max_len = strlen(token);
        token_len = max_len;
        trimmed = trim_whitespace(token, &token_len);
        
        if (count >= capacity) {
            char **new_items;
            capacity *= 2;
            new_items = realloc(temp_items, capacity * sizeof(char *));
            if (new_items == NULL) {
                for (size_t i = 0; i < count; i++) {
                    free(temp_items[i]);
                }
                free(temp_items);
                free(buffer);
                return -1;
            }
            temp_items = new_items;
        }
        
        temp_items[count] = malloc(token_len + 1);
        if (temp_items[count] == NULL) {
            for (size_t i = 0; i < count; i++) {
                free(temp_items[i]);
            }
            free(temp_items);
            free(buffer);
            return -1;
        }
        if (token_len > 0) {
            memcpy(temp_items[count], trimmed, token_len);
        }
        temp_items[count][token_len] = '\0';
        count++;
        
        token = strtok_r(NULL, ",", &saveptr);
    }
    
    free(buffer);
    
    if (count == 0) {
        free(temp_items);
        result->items = NULL;
        result->count = 0;
        return 0;
    }
    
    result->items = temp_items;
    result->count = count;
    return 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple tuple;
    int status;
    
    status = string_to_tuple(input, strnlen(input, 1024), &tuple);
    if (status != 0) {
        fprintf(stderr, "Error converting string to tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("(");
    for (size_t i = 0; i < tuple.count; i++) {
        printf("\"%s\"", tuple.items[i]);
        if (i < tuple.count - 1) {
            printf(", ");
        }
    }
    printf(")\n");
    
    free_tuple(&tuple);
    
    return EXIT_SUCCESS;
}