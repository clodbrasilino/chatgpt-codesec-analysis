#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'sequence' can be declared as pointer to const [constParameterPointer]
 */
bool value_exists(int *sequence, size_t length, int value) {
    if (sequence == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        if (sequence[i] == value) {
            return true;
        }
    }

    return false;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    bool found = value_exists(arr, len, 3);

    if (found) {
        printf("Value exists\n");
    } else {
        printf("Value does not exist\n");
    }

    return 0;
}