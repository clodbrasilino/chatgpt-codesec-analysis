#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Tuple {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple create_tuple(const char *str, const int *list, size_t list_len) {
    Tuple t;
    memset(&t, 0, sizeof(t));

    if (str == NULL) {
        t.str = NULL;
    } else {
        size_t str_length = strnlen(str, SIZE_MAX);
        
        if (str_length == SIZE_MAX) {
            fprintf(stderr, "String too long or not terminated\n");
            exit(EXIT_FAILURE);
        }
        
        if (str_length > SIZE_MAX - 1) {
            fprintf(stderr, "Size overflow detected\n");
            exit(EXIT_FAILURE);
        }
        
        size_t dest_size = str_length + 1;
        
        t.str = malloc(dest_size);
        if (t.str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        memcpy(t.str, str, str_length);
        t.str[str_length] = '\0';
    }

    t.list_len = list_len;

    if (list == NULL || list_len == 0) {
        t.list = NULL;
    } else {
        if (list_len > SIZE_MAX / sizeof(int)) {
            free(t.str);
            fprintf(stderr, "Integer overflow detected\n");
            exit(EXIT_FAILURE);
        }
        
        size_t alloc_size = list_len * sizeof(int);
        
        t.list = malloc(alloc_size);
        if (t.list == NULL) {
            free(t.str);
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        memcpy(t.list, list, alloc_size);
    }

    return t;
}

void free_tuple(Tuple *t) {
    if (t == NULL) return;
    free(t->str);
    free(t->list);
    t->str = NULL;
    t->list = NULL;
    t->list_len = 0;
}

int main(void) {
    const char *str = "hello";
    const int arr[] = {1, 2, 3, 4, 5};
    Tuple t;

    t = create_tuple(str, arr, 5);

    if (t.str != NULL) {
        printf("String: %s\n", t.str);
    }

    if (t.list != NULL) {
        printf("List: ");
        for (size_t i = 0; i < t.list_len; i++) {
            printf("%d ", t.list[i]);
        }
        printf("\n");
    }

    free_tuple(&t);

    return 0;
}