#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
size_t count_integers(int *list, size_t length) {
    if (list == NULL) return 0;
    return length;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count = count_integers(numbers, sizeof(numbers) / sizeof(numbers[0]));
    printf("Number of integers: %zu\n", count);
    return 0;
}