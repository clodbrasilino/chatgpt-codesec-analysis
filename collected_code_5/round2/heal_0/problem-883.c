#include <stdio.h>

void find_divisible_numbers(int numbers[], int size, int m, int n){
    for(int i=0; i<size; i++){
        if(numbers[i]%m == 0 && numbers[i]%n == 0){
            printf("%d ", numbers[i]);
        }
    }
}

int main() {
    int array[] = {10,15,20,30,35,40,50,60};
    int size = sizeof(array)/sizeof(array[0]);
    int m = 5;
    int n = 10;
    
    printf("Numbers divisible by %d and %d in the given array are: ", m, n);
    find_divisible_numbers(array, size, m, n);
    return 0;
}