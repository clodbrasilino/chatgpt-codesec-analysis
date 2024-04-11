#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* str;
    int* list;
    int list_size;
} Tuple;

Tuple* create_tuple(char* str, int* list, int list_size) {
    Tuple* tuple = (Tuple*) malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple->str = (char*) malloc(strlen(str) + 1);
    strcpy(tuple->str, str);
    tuple->list = (int*) malloc(list_size * sizeof(int));
    memcpy(tuple->list, list, list_size * sizeof(int));
    tuple->list_size = list_size;
    return tuple;
}

void print_tuple(Tuple* tuple) {
    printf("String: %s\n", tuple->str);
    printf("List: ");
    for(int i = 0; i < tuple->list_size; i++) {
        printf("%d ", tuple->list[i]);
    }
    printf("\n");
}

void free_tuple(Tuple* tuple) {
    free(tuple->str);
    free(tuple->list);
    free(tuple);
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    Tuple* tuple = create_tuple("Hello", list, 5);
    print_tuple(tuple);
    free_tuple(tuple);
    return 0;
}