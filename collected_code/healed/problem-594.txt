#include <stdio.h>

int findDifference(const int* list, int size) {
    int even = -1;
    int odd = -1;

    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0 && even == -1) {
            even = list[i];
            continue;
        }

        if (list[i] % 2 != 0 && odd == -1) {
            odd = list[i];
            continue;
        }

        if (even != -1 && odd != -1) {
            break;
        }
    }

    if (even == -1 || odd == -1) {
        return -1;
    }

    return even - odd;
}

int main() {
    int array[] = {2,7,8,10,15};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Difference: %d\n", findDifference(array, size));

    return 0;
}