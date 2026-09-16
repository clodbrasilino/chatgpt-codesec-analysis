#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int countEqualPairs(int *array, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int array[] = {1, 2, 3, 2, 4, 1};
    int size = sizeof(array) / sizeof(array[0]);
    int result = countEqualPairs(array, size);
    printf("Number of equal pairs: %d\n", result);
    return 0;
}