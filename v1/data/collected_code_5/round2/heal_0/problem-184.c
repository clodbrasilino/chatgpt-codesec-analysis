#include <stdio.h>
#include <stdlib.h>

void find_greater_values(int *array, int len, int value) {
    int i;
    for(i = 0; i < len; i++) {
        if(array[i] > value) {
            printf("%d ", array[i]);
        }
    }
}

int main() {
    int *ptr, i , num, val;
    
    printf("Enter number of elements: ");
    scanf("%d",&num);
    ptr = (int*)malloc(num * sizeof(int));
    
    for(i = 0; i < num; i++) {
        printf("Enter element %d : ",i+1);
        scanf("%d", ptr + i);
    }

    printf("Enter the value: ");
    scanf("%d",&val);

    printf("Values greater than %d are: ", val);
    find_greater_values(ptr, num, val);

    free(ptr);

    return 0;
}