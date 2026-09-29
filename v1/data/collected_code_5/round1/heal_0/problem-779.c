#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool isListUnique(int arr[MAX_SIZE][MAX_SIZE], int n, int* list, int list_size) {
    for(int i = 0; i < n; i++) {
        if(arr[i][0] != list_size) continue;
        bool is_same = true;
        for(int j = 1; j <= list_size; j++) {
            if(arr[i][j] != list[j - 1]) {
                is_same = false;
                break;
            }
        }
        if(is_same) return false;
    }
    return true;
}

int countUniqueLists(int arr[MAX_SIZE][MAX_SIZE], int n) {
    int unique_count = 0;
    for(int i = 0; i < n; i++) {
        if(isListUnique(arr, i, &arr[i][1], arr[i][0])) unique_count++;
    }
    return unique_count;
}

int main() {
    int arr[MAX_SIZE][MAX_SIZE], n;
    printf("Enter the number of lists: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter the size of list %d: ", i + 1);
        scanf("%d", &arr[i][0]);
        printf("Enter the elements of list %d: ", i + 1);
        for(int j = 1; j <= arr[i][0]; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int unique_count = countUniqueLists(arr, n);
    printf("The number of unique lists is: %d\n", unique_count);

    return 0;
}