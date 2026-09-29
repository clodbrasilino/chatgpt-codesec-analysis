#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_first_position(int *array, size_t size, int target) {
    if (array == NULL || size == 0) {
        return -1;
    }

    long long low = 0;
    long long high = (long long)size - 1;
    int result = -1;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (array[mid] == target) {
            result = (int)mid;
            high = mid - 1;
        } else if (array[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

int main(void) {
    int array[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    size_t size = sizeof(array) / sizeof(array[0]);

    int target = 2;
    int pos = find_first_position(array, size, target);
    printf("%d\n", pos);

    target = 5;
    pos = find_first_position(array, size, target);
    printf("%d\n", pos);

    target = 7;
    pos = find_first_position(array, size, target);
    printf("%d\n", pos);

    pos = find_first_position(NULL, size, target);
    printf("%d\n", pos);

    pos = find_first_position(array, 0, target);
    printf("%d\n", pos);

    return 0;
}