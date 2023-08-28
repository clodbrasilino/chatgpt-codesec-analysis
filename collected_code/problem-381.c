#include <stdio.h>

void sortListOfLists(int list[][3], int size, int index) {
    int i, j, temp;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (list[j][index] > list[j + 1][index]) {
                for (int k = 0; k < 3; k++) {
                    temp = list[j][k];
                    list[j][k] = list[j + 1][k];
                    list[j + 1][k] = temp;
                }
            }
        }
    }
}

int main() {
    int list[4][3] = {{5, 6, 3}, {4, 9, 2}, {8, 1, 4}, {7, 3, 1}};
    int size = sizeof(list) / sizeof(list[0]);
    int index = 1;

    sortListOfLists(list, size, index);

    printf("Sorted list of lists by index %d:\n", index);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}