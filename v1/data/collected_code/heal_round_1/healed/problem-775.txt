#include <stdio.h>

int checkOddIndex(const int arr[], int size) {
    for (int i = 1; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int list[] = {3, 5, 2, 7, 9, 4};
    int size = sizeof(list) / sizeof(list[0]);

    int result = checkOddIndex(list, size);

    if (result) {
        printf("Every odd index contains odd numbers\n");
    } else {
        printf("Not every odd index contains odd numbers\n");
    }

    return 0;
}