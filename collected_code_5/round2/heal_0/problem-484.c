#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tuple {
    int var1;
    int var2;
} tuple;

int isEqual(tuple *t1, tuple *t2) {
    if(t1->var1 == t2->var1 && t1->var2 == t2->var2)
        return 1;
    else
        return 0;
}

tuple* remove_matching_tuples(tuple *tArray1, tuple *tArray2, int size1, int size2) {
    int matchFound = 0;
    tuple *resultArray = (tuple*)malloc(sizeof(tuple) * size1);

    for(int i = 0; i<size1; i++){
        for(int j = 0; j<size2; j++){
            if(isEqual(&tArray1[i], &tArray2[j])) {
                matchFound = 1;
                break;
            }
        }
        
        if(!matchFound)
            resultArray[i] = tArray1[i];  
         
        matchFound = 0;
    }
    
    return resultArray;
}

int main() {
    tuple tArray1[3] = {{1, 2}, {3, 4},{5, 6}};
    tuple tArray2[2] = {{1, 2},{5, 6}};

    tuple *resultArray = remove_matching_tuples(tArray1, tArray2, 3, 2);

    for(int i = 0; i<3; i++)
        printf("Tuple %d: {%d, %d}\n", i+1, resultArray[i].var1, resultArray[i].var2);

    free(resultArray);
    return 0;
}