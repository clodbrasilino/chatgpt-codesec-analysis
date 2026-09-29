#include <stdio.h>
#include <stdlib.h>

void findSquare(int* array, int n) {
    for(int i = 0; i < n; i++) {
        array[i] = array[i] * array[i];
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Please, Enter a valid number of elements \n");
        return 0;
    }

    int* array = (int*) malloc(n * sizeof(int));
    if(array == NULL) {
        printf("Memory not allocated.\n");
        return 0;
    }

    printf("Enter elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    findSquare(array, n);

    printf("Squares of elements in the array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    free(array);
    return 0;
}