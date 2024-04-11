#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
    int *elements;
    int size;
} Set;

Set* convertToSet(int tuples[], int size) {
    Set *set = (Set*)malloc(sizeof(Set));
    
    if(set == NULL) {
        return NULL;
    }

    set->elements = (int*)malloc(sizeof(int) * size);
    if(set->elements == NULL) {
        free(set);
        return NULL;
    }

    set->size = 0;

    for(int i = 0; i < size; i++) {
        int j;
        for(j = 0; j < i; j++)
            if(tuples[i] == tuples[j])
                break;
        if(i == j) 
            set->elements[set->size++] = tuples[i];
    }

    return set;
}

void printSet(Set *set) {
    if(set == NULL || set->elements == NULL) {
        return;
    }
    printf("{ ");
    for(int i = 0; i < set->size; i++)
        printf("%d ", set->elements[i]);
    printf("}\n");
}

int main() {
    int tuples[] = {1, 2, 3, 4, 4, 5, 6, 6, 7};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    Set *set = convertToSet(tuples, size);

    if(set == NULL) {
        return 1;
    }

    printSet(set);

    free(set->elements);
    free(set);

    return 0;
}