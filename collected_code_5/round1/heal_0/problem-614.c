#include <stdio.h>

// a function to find the cumulative sum of a given list of values
int cumulative_sum(int *array, int length){
    int sum = 0;
    for(int i = 0; i<length; i++){
        sum += array[i];
    }
    return sum;
}

int main(){
    int array[] = {1,2,3,4,5};
    int length = sizeof(array) / sizeof(array[0]);
    printf("Sum is: %d\n", cumulative_sum(array, length));
    return 0;
}