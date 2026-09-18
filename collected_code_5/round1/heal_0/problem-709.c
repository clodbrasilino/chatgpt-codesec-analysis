#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tuple {
    int key;
    int value;
};

int uniqueKeyCount(struct tuple tuples[], int size, int value){
    int i, j, count = 0;
    int* uniqueKeys;

    uniqueKeys = (int*) malloc(size * sizeof(int));
    if(uniqueKeys == NULL){
       printf("Memory not allocated.\n");
       exit(0);
    }

    for(i = 0; i < size; i++)
       uniqueKeys[i] = -1;

    for(i = 0; i < size; i++){
        if(tuples[i].value == value){
            for(j = 0; j < count; j++){
                if(tuples[i].key == uniqueKeys[j])
                    break;
            }
            if(j == count){
                uniqueKeys[count] = tuples[i].key;
                count++;
            }
        }
    }

    free(uniqueKeys);

    return count;
}

int main(int argc, char* argv[]){
    struct tuple tuples[] = {
        {1, 22}, {2, 33}, {3, 44},
        {4, 33}, {5, 22}, {6, 44},
        {7, 44}, {1, 22}, {2, 33}
    };

    int value = 33; // change to your specific value
    int size = sizeof(tuples) / sizeof(tuples[0]);

    int count = uniqueKeyCount(tuples, size, value);

    printf("Value %d has %d unique keys\n", value, count);

    return 0;
}