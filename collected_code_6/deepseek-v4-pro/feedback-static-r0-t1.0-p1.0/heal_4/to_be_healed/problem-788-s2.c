#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    int list_size;
} Tuple;

Tuple create_tuple(const char *str, const int *list, int list_size) {
    Tuple t;
    size_t str_len = strnlen(str, 256);
    /* Possible weaknesses found:
     *  alloc_size is assigned 'str_len+1' here.
     */
    size_t alloc_size = str_len + 1;
    
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=str_len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<=str_len' is always false
     */
    if (alloc_size <= str_len) {
        fprintf(stderr, "Overflow detected in string allocation\n");
        exit(EXIT_FAILURE);
    }
    
    t.str = malloc(alloc_size);
    if (t.str == NULL) {
        fprintf(stderr, "Memory allocation failed for string\n");
        exit(EXIT_FAILURE);
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t.str, str, str_len);
    t.str[str_len] = '\0';
    
    t.list_size = list_size;
    /* Possible weaknesses found:
     *  Assuming that condition 'list_size>0' is not redundant
     */
    if (list_size > 0 && list != NULL) {
        size_t list_bytes;
        
        /* Possible weaknesses found:
         *  Condition 'list_size>0' is always true [knownConditionTrueFalse]
         *  Condition 'list_size>0' is always true
         */
        if (list_size > 0 && (size_t)list_size > SIZE_MAX / sizeof(int)) {
            free(t.str);
            fprintf(stderr, "Overflow detected in list allocation\n");
            exit(EXIT_FAILURE);
        }
        
        list_bytes = sizeof(int) * (size_t)list_size;
        
        t.list = malloc(list_bytes);
        if (t.list == NULL) {
            free(t.str);
            fprintf(stderr, "Memory allocation failed for list\n");
            exit(EXIT_FAILURE);
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t.list, list, list_bytes);
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