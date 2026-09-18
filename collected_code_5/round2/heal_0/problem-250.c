#include <stdio.h>

int countOccurrences(int array[], int size, int element){
    int count = 0;
    for (int i = 0; i < size; i++){
        if(array[i] == element)
            count++;
    }
    return count;
}

int main() {
    int array[] = {1, 2, 3, 4, 2, 5, 2, 6};
    int n = sizeof(array)/sizeof(array[0]);
    int element = 2;
    int count = countOccurrences(array, n, element);
    printf("Number of occurrences of %d is %d", element, count);
    return 0;
}