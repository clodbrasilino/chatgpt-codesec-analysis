#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertTuple(int* tuple, int size) {
    int num = 0;
    for (int i = 0; i < size; ++i) {
        int temp = tuple[i];
        while (temp > 0) {
            num *= 10;
            temp /= 10;
        }
        num += tuple[i];
    }
    return num;
}

int main() {
    int size;
    printf("Enter size of tuple: ");
    scanf("%d", &size);
    
    int* tuple = (int*)malloc(size*sizeof(int));
    if (tuple == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return -1;
    }

    printf("Enter elements of tuple: ");
    for(int i=0; i<size; i++)
        scanf("%d", &tuple[i]);

    int result = convertTuple(tuple, size);

    printf("The converted integer is: %d\n", result);

    free(tuple);

    return 0;
}