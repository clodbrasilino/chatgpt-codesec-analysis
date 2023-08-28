#include <stdio.h>

void extractSinglyElement(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count == 1) {
            printf("%d ", arr[i]);
        }
    }
}

int main() {
    int tupleList[] = {1, 2, 3, 4, 2, 3, 4, 5};
    int n = sizeof(tupleList) / sizeof(tupleList[0]);

    extractSinglyElement(tupleList, n);

    return 0;
}