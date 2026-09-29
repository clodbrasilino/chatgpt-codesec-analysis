#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

char* convertTupleToString(Tuple* t){
    char* result;
    if(t != NULL){
        result = (char*) malloc(1000 * sizeof(char));
        if(result != NULL){
            sprintf(result, "(%d, %d)", t->x, t->y);
        }else{
            printf("Memory allocation failed.\n");
            return NULL;
        }
    }else{
        printf("Tuple is NULL.\n");
        return NULL;
    }
    return result;
}

int main(){
    Tuple t = {5, 10};
    char* tupleStr = convertTupleToString(&t);
    if(tupleStr != NULL){
        printf("Tuple as string : %s\n", tupleStr);
        free(tupleStr);
    }
    return 0;
}