#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
} List;

typedef struct {
    char **data;
    int size;
} Tuple;

List* tupleToList(Tuple *tuple, char *str) {
    List *list = malloc(sizeof(List));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list->size = tuple->size * 2;
    list->data = malloc(list->size * sizeof(char*));

    for(int i = 0, j = 0; i < tuple->size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*list.data + (long unsigned int)j * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list->data[j++] = tuple->data[i];
        list->data[j++] = str;
    }

    return list;
}

int main() {
    Tuple tuple;
    tuple.size = 3;
    tuple.data = malloc(tuple.size * sizeof(char*));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple.data[0] = "Hello";
    tuple.data[1] = "World";
    tuple.data[2] = "!";

    char *str = "Add";

    List *list = tupleToList(&tuple, str);

    for(int i = 0; i < list->size; i++) {
        printf("%s ", list->data[i]);
    }

    free(tuple.data);
    free(list->data);
    free(list);

    return 0;
}