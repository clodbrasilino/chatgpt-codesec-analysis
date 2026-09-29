#include<stdio.h>
typedef struct {
    int dataType;
    void *data;
} Tuple;

int checkDataTypeConsistency(Tuple* tupleArray, int size){
    int dataType = tupleArray[0].dataType;
    for (int i = 1; i < size; i++)
        if(tupleArray[i].dataType != dataType)
            return 0;
    return 1;
}

int main(){
    Tuple tupleArray[3];
    tupleArray[0].dataType = 1;
    tupleArray[1].dataType = 1;
    tupleArray[2].dataType = 1;

    int result = checkDataTypeConsistency(tupleArray, 3);
    printf("%d", result);
    return 0;
}