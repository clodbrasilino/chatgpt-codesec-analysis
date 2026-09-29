#include <stdio.h>

int findMissingNumber(int array[], int n) {
    int i, total;
    total = (n + 1)*(n + 2)/2;    
    for(i = 0; i< n; i++)
        total -= array[i];
    return total;
}

int main() {
    int array[] = {1, 2, 4, 6, 3, 7, 8};
    int missing_number = findMissingNumber(array, 7);
    printf("The smallest missing number is %d ", missing_number);
    return 0;
}