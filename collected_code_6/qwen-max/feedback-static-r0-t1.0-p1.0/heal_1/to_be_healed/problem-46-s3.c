#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
bool areAllNumbersDifferent(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (array[i] == array[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int numbers[] = {5, 3, 7, 1, 9, 2};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    if (areAllNumbersDifferent(numbers, n)) {
        printf("All numbers are different.\n");
    } else {
        printf("There are some duplicate numbers.\n");
    }

    return 0;
}