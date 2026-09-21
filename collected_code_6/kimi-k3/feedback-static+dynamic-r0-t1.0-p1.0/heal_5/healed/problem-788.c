#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size) {
    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    if (list_size > 0 && list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    size_t str_len = strnlen(str, 1024);
    if (str_len == SIZE_MAX) {
        free(tuple);
        return NULL;
    }
    
    tuple->str = (char *)malloc(str_len + 1);
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }
    
    memcpy(tuple->str, str, str_len);
    tuple->str[str_len] = '\0';

    tuple->list_size = list_size;
    if (list_size > 0) {
        size_t list_bytes = list_size * sizeof(int);
        if (list_bytes / sizeof(int) != list_size) {
            free(tuple->str);
            free(tuple);
            return NULL;
        }
        
        tuple->list = (int *)malloc(list_bytes);
        if (tuple->list == NULL) {
            free(tuple->str);
            free(tuple);
            return NULL;
        }
        
        memcpy(tuple->list, list, list_bytes);
    } else {
        tuple->list = NULL;
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple->list);
        free(tuple);
    }
}

int main(void) {
    const char *str = "example";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = create_tuple(str, list, list_size);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", tuple->str);
    printf("List: ");
    for (size_t i = 0; i < tuple->list_size; i++) {
        printf("%d ", tuple->list[i]);
    }
    printf("\n");

    free_tuple(tuple);

    return EXIT_SUCCESS;
}