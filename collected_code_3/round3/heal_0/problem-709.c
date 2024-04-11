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
    struct Tuple arr[] = {{1, 10}, {2, 20}, {3, 20}, {4, 30}, {2, 20}, {5, 30}, {6, 40}, {7, 10}};
    int n = sizeof(arr) / sizeof(arr[0]);
    int value = 20;
    printf("Count of unique keys for value %d is %d\n", value, countUniqueKeys(arr, n, value));
    return 0;
}