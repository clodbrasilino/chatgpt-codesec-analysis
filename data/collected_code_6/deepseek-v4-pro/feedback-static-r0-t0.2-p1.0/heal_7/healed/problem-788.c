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
    size_t str_len = strnlen(str, 1024);
    
    t.str = (char *)malloc(str_len + 1);
    if (t.str == NULL) {
        exit(EXIT_FAILURE);
    }
    
    if (str_len > 0) {
        if (str_len + 1 > str_len) {
            memcpy(t.str, str, str_len);
        }
    }
    t.str[str_len] = '\0';
    
    t.list = NULL;
    t.list_len = 0;
    
    if (list_len > 0 && list != NULL) {
        if (list_len > (size_t)-1 / sizeof(int)) {
            free(t.str);
            exit(EXIT_FAILURE);
        }
        
        size_t alloc_size = list_len * sizeof(int);
        
        t.list = (int *)malloc(alloc_size);
        if (t.list == NULL) {
            free(t.str);
            exit(EXIT_FAILURE);
        }
        
        if (alloc_size <= (size_t)-1) {
            memcpy(t.list, list, alloc_size);
            t.list_len = list_len;
        } else {
            free(t.list);
            free(t.str);
            exit(EXIT_FAILURE);
        }
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
    int list[] = {1, 2, 3, 4, 5};
    size_t list_len = sizeof(list) / sizeof(list[0]);
    
    Tuple t = create_tuple(str, list, list_len);
    
    printf("String: %s\n", t.str);
    printf("List: ");
    for (size_t i = 0; i < t.list_len; i++) {
        printf("%d ", t.list[i]);
    }
    printf("\n");
    
    free_tuple(&t);
    
    return 0;
}