#include <stdio.h>

#define MAX 1000

void ModuloLists(int arr1[], int arr2[], int size)
{
    int result[MAX];
    for(int i = 0; i < size; i++) {
        if(arr2[i] != 0) {
            result[i] = arr1[i] % arr2[i];
        } else {
            printf("Division by zero is not defined. Skipping this operation.\n");
            continue;
        }
    printf("Result at position %d is %d\n", i, result[i]);
    }
}

int main()
{
    int arr1[] = {10, 20, 30, 40, 50};
    int arr2[] = {2, 4, 0, 8, 10};
    int size = sizeof(arr1)/sizeof(arr1[0]);
    ModuloLists(arr1, arr2, size);
    return 0;
}