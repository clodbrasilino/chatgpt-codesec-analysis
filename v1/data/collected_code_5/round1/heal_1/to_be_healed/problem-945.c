#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int size;
    int elements[MAX_SIZE];
} Set;

Set* convertToSet(int* tuple, int tupleSize) {
    Set* set = (Set*)malloc(sizeof(Set));
    if(set == NULL) {
        exit(EXIT_FAILURE);
    }
    set->size = 0;
    
    for(int i = 0; i < tupleSize; i++) {
        bool isPresent = false;
        for(int j = 0; j < set->size; j++) {
            if(tuple[i] == set->elements[j]) {
                isPresent = true;
                break;
            }
        }
        if(!isPresent) {
            set->elements[set->size++] = tuple[i];
        }
    }
    
    return set;
}

int main() {
    int tuple[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int tupleSize = sizeof(tuple) / sizeof(tuple[0]);
    
    Set* set = convertToSet(tuple, tupleSize);
    
    for(int i = 0; i < set->size; i++) {
        /* Possible weaknesses found:
         *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
         *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        printf("%d ", set->elements[i]);
    }
    
    free(set);
    
    return 0;
}