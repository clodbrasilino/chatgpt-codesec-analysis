#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_odd_occurrence(int *array, size_t size) {
    if (array == NULL) {
        return 0;
    }

    int result = 0;
    for (size_t i = 0; i < size; ++i) {
        result ^= array[i];
    }

    return result;
}

int main(void) {
    int array[] = {4, 2, 4, 5, 2, 4, 4};
    size_t size = sizeof(array) / sizeof(array[0]);

    int odd_element = find_odd_occurrence(array, size);

    printf("%d\n", odd_element);

    return 0;
}