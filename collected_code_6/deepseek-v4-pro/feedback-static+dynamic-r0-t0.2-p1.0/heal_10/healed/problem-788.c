#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple create_tuple(const char *str, const int *list, size_t list_len) {
    Tuple t;
    size_t str_len;
    
    t.str = NULL;
    t.list = NULL;
    t.list_len = 0;
    
    if (str == NULL) {
        str_len = 0;
    } else {
        str_len = strnlen(str, SIZE_MAX);
        if (str_len == SIZE_MAX) {
            return t;
        }
    }
    
    if (list_len > SIZE_MAX / sizeof(int)) {
        return t;
    }
    
    if (str_len > 0 && str != NULL) {
        size_t alloc_size = str_len + 1;
        if (alloc_size <= str_len) {
            return t;
        }
        t.str = (char *)malloc(alloc_size);
        if (t.str == NULL) {
            return t;
        }
        memcpy(t.str, str, str_len);
        t.str[str_len] = '\0';
    } else if (str != NULL) {
        t.str = (char *)malloc(1);
        if (t.str == NULL) {
            return t;
        }
        t.str[0] = '\0';
    }
    
    if (list == NULL && list_len > 0) {
        free(t.str);
        t.str = NULL;
        return t;
    }
    
    if (list_len > 0 && list != NULL) {
        size_t alloc_size = list_len * sizeof(int);
        if (alloc_size == 0 || alloc_size / sizeof(int) != list_len) {
            free(t.str);
            t.str = NULL;
            return t;
        }
        t.list = (int *)malloc(alloc_size);
        if (t.list == NULL) {
            free(t.str);
            t.str = NULL;
            return t;
        }
        memcpy(t.list, list, alloc_size);
    }
    
    t.list_len = list_len;
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        if (t->str != NULL) {
            free(t->str);
            t->str = NULL;
        }
        if (t->list != NULL) {
            free(t->list);
            t->list = NULL;
        }
        t->list_len = 0;
    }
}

int main(void) {
    const char *str = "hello";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_len = sizeof(list) / sizeof(list[0]);
    
    Tuple t = create_tuple(str, list, list_len);
    
    if (t.str == NULL || t.list == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        free_tuple(&t);
        return EXIT_FAILURE;
    }
    
    printf("String: %s\n", t.str);
    printf("List: ");
    for (size_t i = 0; i < t.list_len; i++) {
        printf("%d ", t.list[i]);
    }
    printf("\n");
    
    free_tuple(&t);
    
    return 0;
}