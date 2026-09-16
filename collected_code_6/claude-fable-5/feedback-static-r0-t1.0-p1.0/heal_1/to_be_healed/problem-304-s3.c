#include <stdio.h>
#include <stdlib.h>

int findElement(const int arr[], int arrSize, const int ranges[][2],
                int rotations, int index)
{
    int i;
    /* Possible weaknesses found:
     *  The scope of the variable 'left' can be reduced. [variableScope]
     */
    int left;
    /* Possible weaknesses found:
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    int right;

    if (arr == NULL || ranges == NULL) {
        fprintf(stderr, "Invalid input pointers\n");
        exit(EXIT_FAILURE);
    }

    if (arrSize <= 0 || index < 0 || index >= arrSize) {
        fprintf(stderr, "Invalid array size or index\n");
        exit(EXIT_FAILURE);
    }

    for (i = rotations - 1; i >= 0; i--) {
        left = ranges[i][0];
        right = ranges[i][1];

        if (left < 0 || right >= arrSize || left > right) {
            fprintf(stderr, "Invalid rotation range\n");
            exit(EXIT_FAILURE);
        }

        if (index >= left && index <= right) {
            if (index == left) {
                index = right;
            } else {
                index = index - 1;
            }
        }
    }

    return arr[index];
}

int main(void)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int arrSize = (int)(sizeof(arr) / sizeof(arr[0]));
    int ranges[][2] = { { 0, 2 }, { 0, 3 } };
    int rotations = 2;
    int index = 1;
    int result;

    result = findElement(arr, arrSize, ranges, rotations, index);

    if (printf("Element at index %d is %d\n", index, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}