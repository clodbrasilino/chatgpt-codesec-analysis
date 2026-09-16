#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_smallest(int *list, int size) {
    if (size <= 0) {
        return INT_MAX;
    }
    int smallest = list[0];
    for (int i = 1; i < size; ++i) {
        if (list[i] < smallest) {
            smallest = list[i];
        }
    }
    return smallest;
}

int main() {
    int numbers[] = {34, -50, 42, 14, 0, -8};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int smallest = find_smallest(numbers, size);
    printf("The smallest number is: %d\n", smallest);
    return 0;
}