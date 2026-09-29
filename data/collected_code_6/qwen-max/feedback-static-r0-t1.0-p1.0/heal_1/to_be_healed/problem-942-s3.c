#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
bool isElementInList(int *list, int size, int element) {
    for (int i = 0; i < size; i++) {
        if (list[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int element = 3;

    if (isElementInList(list, size, element)) {
        printf("Element %d is in the list.\n", element);
    } else {
        printf("Element %d is not in the list.\n", element);
    }

    return 0;
}