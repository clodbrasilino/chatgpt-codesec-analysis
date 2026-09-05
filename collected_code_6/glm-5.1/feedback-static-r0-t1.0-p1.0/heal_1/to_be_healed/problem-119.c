#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_single(int *arr, int size) {
    int low = 0;
    int high = size - 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    int mid;
    /* Possible weaknesses found:
     *  The scope of the variable 'half' can be reduced. [variableScope]
     */
    int half;

    while (low < high) {
        mid = low + (high - low) / 2;
        half = mid - low;

        if (half % 2 != 0) {
            if (arr[mid] == arr[mid - 1]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        } else {
            if (arr[mid] == arr[mid + 1]) {
                low = mid + 2;
            } else {
                high = mid;
            }
        }
    }

    return arr[low];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    if (size % 2 == 0) {
        free(arr);
        return EXIT_FAILURE;
    }

    int result = find_single(arr, size);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}