#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int key;
    int value;
};

int countUniqueKeys(struct Tuple *arr, int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].value == value) {
            int j;
            for (j = 0; j < i; j++)
                if (arr[i].key == arr[j].key)
                    break;
            if (i == j)
                count++;
        }
    }
    return count;
}

int main() {
    struct Tuple arr[] = {{1, 10}, {2, 20}, {3, 10}, {4, 20}, {5, 10}, {6, 20}, {7, 10}, {8, 20}, {9, 10}, {10, 20}};
    int n = sizeof(arr) / sizeof(arr[0]);
    int value = 10;
    printf("Number of unique keys for value %d is %d\n", value, countUniqueKeys(arr, n, value));
    return 0;
}