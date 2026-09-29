#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple create_tuple(const char *str, const int *list, size_t list_len) {
    Tuple t;
    size_t str_len;
    
    if (str == NULL) {
        str_len = 0;
    } else {
        str_len = strnlen(str, 1024);
    }
    
    t.str = malloc(str_len + 1);
    if (t.str == NULL) {
        exit(EXIT_FAILURE);
    }
    
    if (str_len > 0 && str != NULL) {
        memcpy(t.str, str, str_len);
        t.str[str_len] = '\0';
    } else {
        t.str[0] = '\0';
    }
    
    if (list_len > 0 && list != NULL) {
        size_t alloc_size = list_len * sizeof(int);
        if (alloc_size / sizeof(int) != list_len) {
            free(t.str);
            t.str = NULL;
            exit(EXIT_FAILURE);
        }
        t.list = malloc(alloc_size);
        if (t.list == NULL) {
            free(t.str);
            t.str = NULL;
            exit(EXIT_FAILURE);
        }
        memcpy(t.list, list, alloc_size);
        t.list_len = list_len;
    } else {
        t.list = NULL;
        t.list_len = 0;
    }
    
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        t->str = NULL;
        t->list = NULL;
        t->list_len = 0;
    }
}

int main(void) {
    const char *str = "hello";
    int arr[] = {1, 2, 3, 4, 5};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    
    Tuple t = create_tuple(str, arr, arr_len);
    
    printf("String: %s\n", t.str);
    printf("List: ");
    for (size_t i = 0; i < t.list_len; i++) {
        printf("%d ", t.list[i]);
    }
    printf("\n");
    
    free_tuple(&t);
    
    return 0;
}