#include <stdio.h>
#include <stdlib.h>

int sum_of_consecutive(const int *numbers, int count) {
    if (numbers == NULL || count < 0) {
        return 0;
    }
    
    int sum = 0;
    int i = 0;
    
    while (i < count) {
        int current = numbers[i];
        
        if (i + 1 < count && numbers[i + 1] == current + 1) {
            int j = i + 1;
            while (j < count && numbers[j] == numbers[j - 1] + 1) {
                sum += numbers[j];
                j++;
            }
            sum += current;
            i = j;
        } else {
            i++;
        }
    }
    
    return sum;
}

int main(void) {
    int test1[] = {1, 2, 3, 4, 5};
    printf("%d\n", sum_of_consecutive(test1, 5));
    
    int test2[] = {1, 3, 4, 5, 8, 9};
    printf("%d\n", sum_of_consecutive(test2, 6));
    
    int test3[] = {5};
    printf("%d\n", sum_of_consecutive(test3, 1));
    
    int test4[] = {10, 20, 30};
    printf("%d\n", sum_of_consecutive(test4, 3));
    
    return 0;
}