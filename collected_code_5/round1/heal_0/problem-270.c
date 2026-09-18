#include <stdio.h>
#include <stdlib.h>

int sumOfEvenNumbers(int array[], int size) {
    int sum = 0;
    
    for (int i = 0; i < size; i += 2) {
        if (array[i] % 2 == 0) {
            sum += array[i];
        }
    }
    
    return sum;
}

int main() {
    int num, sum;
    printf("Input the number of elements to be stored in the array: ");
    scanf("%d", &num);
    
    int *array = malloc(num * sizeof(int));
    
    if (array == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    
    printf("Input elements in the array:\n");
    for (int i = 0; i < num; i++) {
        printf("Element-%d: ", i);
        scanf("%d", &array[i]);
    }
    sum = sumOfEvenNumbers(array, num);
    printf("Sum of even elements at even index positions: %d\n", sum);
    free(array);

    return 0;
}