#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    char *str;
    int *list;
    int list_size;
} Tuple;

Tuple create_tuple(const char *str, const int *list, int list_size) {
    Tuple t;
    t.str = NULL;
    t.list = NULL;
    t.list_size = 0;
    
    if (str == NULL) {
        fprintf(stderr, "String pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    
    size_t str_len = strnlen(str, 4096);
    
    if (str_len == 4096 && str[4096] != '\0') {
        fprintf(stderr, "String too long or not null-terminated\n");
        exit(EXIT_FAILURE);
    }
    
    if (str_len > SIZE_MAX - 1) {
        fprintf(stderr, "String length overflow\n");
        exit(EXIT_FAILURE);
    }
    
    t.str = malloc(str_len + 1);
    if (t.str == NULL) {
        fprintf(stderr, "Memory allocation failed for string\n");
        exit(EXIT_FAILURE);
    }
    
    if (str_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t.str, str, str_len);
    }
    t.str[str_len] = '\0';
    
    t.list_size = list_size;
    if (list_size > 0) {
        if (list == NULL) {
            free(t.str);
            t.str = NULL;
            fprintf(stderr, "List pointer is NULL with non-zero size\n");
            exit(EXIT_FAILURE);
        }
        if (list_size > SIZE_MAX / sizeof(int)) {
            free(t.str);
            t.str = NULL;
            fprintf(stderr, "Integer overflow detected in list allocation\n");
            exit(EXIT_FAILURE);
        }
        size_t alloc_size = sizeof(int) * list_size;
        t.list = malloc(alloc_size);
        if (t.list == NULL) {
            free(t.str);
            t.str = NULL;
            fprintf(stderr, "Memory allocation failed for list\n");
            exit(EXIT_FAILURE);
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t.list, list, alloc_size);
    } else {
        t.list = NULL;
    }
    
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        t->str = NULL;
        t->list = NULL;
        t->list_size = 0;
    }
}

int main(void) {
    const char *str = "hello";
    int list_data[] = {1, 2, 3, 4, 5};
    int list_size = sizeof(list_data) / sizeof(list_data[0]);
    
    Tuple t = create_tuple(str, list_data, list_size);
    
    printf("String: %s\n", t.str);
    printf("List: ");
    for (int i = 0; i < t.list_size; i++) {
        printf("%d ", t.list[i]);
    }
    printf("\n");
    
    free_tuple(&t);
    
    return 0;
}