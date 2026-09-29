#include <stdio.h>

void rearrange(int *array, int arraySize)
{
    int i = -1;
    for (int j = 0; j < arraySize; j++) {
        if (array[j] < 0) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

int main(){
    int array[] = {-1, 2, -3, 4, 5, -6, 7, 8, 9};
    int arraySize = sizeof(array) / sizeof(array[0]);

    rearrange(array, arraySize);

    for (int i = 0; i < arraySize; i++)
        printf("%d ", array[i]);

    return 0;
}