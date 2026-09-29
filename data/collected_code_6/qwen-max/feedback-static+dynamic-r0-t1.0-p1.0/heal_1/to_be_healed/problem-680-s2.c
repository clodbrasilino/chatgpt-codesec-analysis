#include <stdbool.h>
#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
bool is_increasing_trend(int *numbers, int length) {
    for (int i = 1; i < length; i++) {
        if (numbers[i] <= numbers[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int numbers[] = {1, 3, 5, 7, 9};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    if (is_increasing_trend(numbers, length)) {
        printf("The sequence has an increasing trend.\n");
    } else {
        printf("The sequence does not have an increasing trend.\n");
    }

    return 0;
}