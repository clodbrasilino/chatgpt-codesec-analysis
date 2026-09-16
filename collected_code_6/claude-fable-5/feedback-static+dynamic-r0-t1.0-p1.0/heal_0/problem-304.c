#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    int right;
} Range;

int find_element(const int *arr, int n, const Range *rotations,
                 int num_rotations, int index, int *result)
{
    int i;

    if (arr == NULL || result == NULL || n <= 0 || index < 0 || index >= n) {
        return -1;
    }

    if (num_rotations > 0 && rotations == NULL) {
        return -1;
    }

    for (i = num_rotations - 1; i >= 0; i--) {
        int left = rotations[i].left;
        int right = rotations[i].right;

        if (left < 0 || right >= n || left > right) {
            return -1;
        }

        if (index >= left && index <= right) {
            if (index == left) {
                index = right;
            } else {
                index = index - 1;
            }
        }
    }

    *result = arr[index];
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    Range rotations[] = {{0, 2}, {0, 3}};
    int num_rotations = (int)(sizeof(rotations) / sizeof(rotations[0]));
    int index = 1;
    int result = 0;

    if (find_element(arr, n, rotations, num_rotations, index, &result) != 0) {
        fprintf(stderr, "Error: invalid input parameters\n");
        return EXIT_FAILURE;
    }

    printf("Element at index %d after rotations: %d\n", index, result);

    return EXIT_SUCCESS;
}