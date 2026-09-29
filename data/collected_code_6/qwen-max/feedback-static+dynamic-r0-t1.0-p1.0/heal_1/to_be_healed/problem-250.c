#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
int count_occurrences(int *tuple, int len, int element) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (tuple[i] == element) {
            count++;
        }
    }
    return count;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5, 3, 3, 2, 1};
    int len = sizeof(tuple) / sizeof(tuple[0]);
    int element = 3;
    int count = count_occurrences(tuple, len, element);
    printf("Occurrences of %d: %d\n", element, count);
    return 0;
}