#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int find_max_sum(int arr[][MAX_SIZE], int n) {
    int max_sum = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < MAX_SIZE; j++) {
            sum += arr[i][j];
        }
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}


int main() {
    int n;
    int arr[MAX_SIZE][MAX_SIZE];

    printf("Enter the number of lists: ");
    scanf("%d", &n);
    if (n > MAX_SIZE) {
        printf("The maximum number of lists is %d. Exiting.\n", MAX_SIZE);
        return EXIT_FAILURE;
    }

    printf("Enter the elements of the lists: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int max_sum = find_max_sum(arr, n);
    printf("The maximum sum of elements in a list is %d.\n", max_sum);
    return EXIT_SUCCESS;
}