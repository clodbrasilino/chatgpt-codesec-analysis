#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char **elements;
    size_t count;
} StringTuple;

typedef struct {
    int *elements;
    size_t count;
} IntTuple;

bool string_tuple_contains(const StringTuple *tuple, const char *k) {
    if (tuple == NULL || k == NULL || tuple->elements == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i] != NULL && strcmp(tuple->elements[i], k) == 0) {
            return true;
        }
    }
    return false;
}

bool int_tuple_contains(const IntTuple *tuple, int k) {
    if (tuple == NULL || tuple->elements == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i] == k) {
            return true;
        }
    }
    return false;
}

StringTuple* create_string_tuple(const char **elements, size_t count) {
    if (elements == NULL || count == 0) {
        return NULL;
    }
    
    StringTuple *tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = malloc(count * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->count = count;
    
    for (size_t i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            tuple->elements[i] = NULL;
            continue;
        }
        
        size_t len = strlen(elements[i]) + 1;
        tuple->elements[i] = malloc(len);
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
        strcpy(tuple->elements[i], elements[i]);
    }
    
    return tuple;
}

IntTuple* create_int_tuple(const int *elements, size_t count) {
    if (elements == NULL || count == 0) {
        return NULL;
    }
    
    IntTuple *tuple = malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = malloc(count * sizeof(int));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->count = count;
    memcpy(tuple->elements, elements, count * sizeof(int));
    
    return tuple;
}

void destroy_string_tuple(StringTuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    if (tuple->elements != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    free(tuple);
}

void destroy_int_tuple(IntTuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    free(tuple->elements);
    free(tuple);
}

int main(void) {
    const char *str_data[] = {"apple", "banana", "cherry", "date"};
    size_t str_count = sizeof(str_data) / sizeof(str_data[0]);
    
    int int_data[] = {10, 20, 30, 40, 50};
    size_t int_count = sizeof(int_data) / sizeof(int_data[0]);
    
    StringTuple *str_tuple = create_string_tuple(str_data, str_count);
    if (str_tuple == NULL) {
        fprintf(stderr, "Failed to create string tuple\n");
        return EXIT_FAILURE;
    }
    
    IntTuple *int_tuple = create_int_tuple(int_data, int_count);
    if (int_tuple == NULL) {
        fprintf(stderr, "Failed to create integer tuple\n");
        destroy_string_tuple(str_tuple);
        return EXIT_FAILURE;
    }
    
    const char *search_str = "banana";
    int search_int = 30;
    
    if (string_tuple_contains(str_tuple, search_str)) {
        printf("String tuple contains: %s\n", search_str);
    } else {
        printf("String tuple does not contain: %s\n", search_str);
    }
    
    if (int_tuple_contains(int_tuple, search_int)) {
        printf("Integer tuple contains: %d\n", search_int);
    } else {
        printf("Integer tuple does not contain: %d\n", search_int);
    }
    
    search_str = "grape";
    search_int = 99;
    
    if (string_tuple_contains(str_tuple, search_str)) {
        printf("String tuple contains: %s\n", search_str);
    } else {
        printf("String tuple does not contain: %s\n", search_str);
    }
    
    if (int_tuple_contains(int_tuple, search_int)) {
        printf("Integer tuple contains: %d\n", search_int);
    } else {
        printf("Integer tuple does not contain: %d\n", search_int);
    }
    
    destroy_string_tuple(str_tuple);
    destroy_int_tuple(int_tuple);
    
    return EXIT_SUCCESS;
}