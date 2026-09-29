#include <stdio.h>

void printNegativeNumbers(int* list, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (list[i] < 0) {
            printf("%d ", list[i]);
        }
    }
    printf("\n");
}

int main() {
    int size, i;

    printf("Enter the size of the list: ");
    scanf("%d", &size);

    if (size > 0) {
        int list[size];

        printf("Enter the elements of the list: ");
        for (i = 0; i < size; i++) {
            scanf("%d", &list[i]);
        }

        printf("\nNegative Numbers in the list are: ");
        printNegativeNumbers(list, size);

    } else {
        printf("Size of list should be greater than 0.\n");
    }
    return 0;
}