#include <stdio.h>

void moduloTupleElements(int size1, int size2, int tuple1[], int tuple2[]){
    if(size1 != size2){
        printf("Error: Sizes of tuples don't match!\n");
        return;
    } 

    for(int i=0; i<size1; i++){
        if(tuple2[i] == 0){
            printf("Error: Division by zero!\n");
            return;
        }
    }

    for(int i = 0; i < size1; i++){
        printf("%d ",tuple1[i] % tuple2[i]);
    }  

    printf("\n");
} 

int main() {
    int tuple1[] = {10, 20, 30, 40, 50};
    int tuple2[] = {2, 3, 5, 7, 11};
    int size1 = sizeof(tuple1)/sizeof(tuple1[0]);
    int size2 = sizeof(tuple2)/sizeof(tuple2[0]);

    moduloTupleElements(size1, size2, tuple1, tuple2);

    return 0;
}