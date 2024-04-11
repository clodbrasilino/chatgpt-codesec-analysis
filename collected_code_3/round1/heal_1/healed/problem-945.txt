#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Set;

Set* convertToSet(int *tuple, int size) {
    Set *set = (Set*)malloc(sizeof(Set));
    if(set == NULL) 
        return NULL;
    
    set->elements = (int*)malloc(sizeof(int) * size);
    if(set->elements == NULL) {
        free(set);
        return NULL;
    }
    set->size = 0;

    for(int i = 0; i < size; i++) {
        int j;
        for(j = 0; j < i; j++)
            if(tuple[i] == tuple[j])
                break;
        if(i == j) 
            set->elements[set->size++] = tuple[i];
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
    if(set == NULL)
        return 1;

    printSet(set);

    free(set->elements);
    free(set);

    return 0;
}