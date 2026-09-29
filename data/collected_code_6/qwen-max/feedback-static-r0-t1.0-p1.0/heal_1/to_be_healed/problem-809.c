#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'second' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'first' can be declared as pointer to const [constParameterPointer]
 */
bool check_tuples(int *first, int *second, int length) {
    for (int i = 0; i < length; ++i) {
        if (second[i] >= first[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int first[] = {5, 3, 7, 2, 8};
    int second[] = {3, 1, 6, 0, 4};
    int length = sizeof(first) / sizeof(first[0]);

    if (check_tuples(first, second, length)) {
        printf("All elements in the second tuple are smaller.\n");
    } else {
        printf("Not all elements in the second tuple are smaller.\n");
    }

    return 0;
}