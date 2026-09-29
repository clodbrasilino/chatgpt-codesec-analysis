#include <stdio.h>
#include <stdlib.h>

void rearrange(int array[], int length) {
    int i = -1;
    for (int j = 0; j < length; j++) {
        if (array[j] < 0) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

int main() {
    int array[] = {2, -5, 3, -4, -1, 0, -6, -7};
    int length = sizeof(array) / sizeof(array[0]);

    rearrange(array, length);

    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);
    printf("\n");
    
    return 0;
}