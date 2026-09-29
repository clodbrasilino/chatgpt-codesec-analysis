#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Set;

Set* convertToSet(int *tuple, int size) {
    Set *set = (Set*)malloc(sizeof(Set));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'set' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    set->elements = (int*)malloc(sizeof(int) * size);
    set->size = 0;

    for(int i = 0; i < size; i++) {
        int j;
        for(j = 0; j < i; j++)
            if(tuple[i] == tuple[j])
                break;

        if(i == j) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*set.elements + (long unsigned int)*set.size * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            set->elements[set->size] = tuple[i];
            set->size++;
        }
    }

    return set;
}

void printSet(Set *set) {
    printf("{ ");
    for(int i = 0; i < set->size; i++)
        printf("%d ", set->elements[i]);
    printf("}\n");
}

int main() {
    int tuple[] = {1, 2, 2, 3, 4, 4, 5, 6, 6, 7};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    Set *set = convertToSet(tuple, size);

    printSet(set);

    free(set->elements);
    free(set);

    return 0;
}