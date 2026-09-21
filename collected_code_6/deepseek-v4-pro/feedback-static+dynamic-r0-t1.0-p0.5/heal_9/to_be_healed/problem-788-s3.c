#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple create_tuple(const char *str, const int *list, size_t list_len) {
    Tuple t;
    size_t str_len;
    size_t list_size;
    
    if (str == NULL || list == NULL || list_len == 0) {
        exit(EXIT_FAILURE);
    }
    
    str_len = strnlen(str, SIZE_MAX);
    if (str_len == SIZE_MAX) {
        exit(EXIT_FAILURE);
    }
    
    t.str = malloc(str_len + 1);
    if (t.str == NULL) {
        exit(EXIT_FAILURE);
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t.str, str, str_len);
    t.str[str_len] = '\0';
    
    if (list_len > SIZE_MAX / sizeof(int)) {
        free(t.str);
        exit(EXIT_FAILURE);
    }
    
    list_size = list_len * sizeof(int);
    
    t.list = malloc(list_size);
    if (t.list == NULL) {
        free(t.str);
        exit(EXIT_FAILURE);
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t.list, list, list_size);
    t.list_len = list_len;
    
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
    size_t len = sizeof(arr) / sizeof(arr[0]);
    
    Tuple t = create_tuple(str, arr, len);
    
    printf("String: %s\n", t.str);
    printf("List: ");
    for (size_t i = 0; i < t.list_len; i++) {
        printf("%d ", t.list[i]);
    }
    printf("\n");
    
    free_tuple(&t);
    
    return 0;
}