#include <stdio.h>

#define ARRAY_SIZE 10

int count_frequency(int arr[], int n, int x) {
    int count = 0;
    for (int i = 0; i < n; i++)
       if (arr[i] == x)
          count++;
    return count;
}

int main() {
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 2, 5, 2, 6, 7, 2};
    int x = 2;
    printf("Frequency of %d = %d", x, count_frequency(arr, ARRAY_SIZE, x));
    return 0;
}