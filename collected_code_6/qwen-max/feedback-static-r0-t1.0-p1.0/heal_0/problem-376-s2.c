#include <stdio.h>
#include <stdlib.h>

void remove_duplicates(int *array, int n, int custom_value) {
    if (n <= 1) return;

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (array[i] == array[j]) {
                array[j] = custom_value;
            }
        }
    }
}

int main() {
    int array[] = {1, 2, 3, 2, 4, 1, 5};
    int n = sizeof(array) / sizeof(array[0]);
    int custom_value = -1;

    remove_duplicates(array, n, custom_value);

    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}