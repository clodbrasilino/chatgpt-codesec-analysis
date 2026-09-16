#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t size, int value)
{
    size_t i;
    for (i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

static int *find_intersection(const int *arr1, size_t size1,
                              const int *arr2, size_t size2,
                              size_t *result_size)
{
    int *result;
    size_t count = 0;
    size_t i;
    size_t max_size;

    if (result_size == NULL) {
        return NULL;
    }
    *result_size = 0;

    if (arr1 == NULL || arr2 == NULL || size1 == 0 || size2 == 0) {
        return NULL;
    }

    max_size = (size1 < size2) ? size1 : size2;

    result = malloc(max_size * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < size1; i++) {
        if (contains(arr2, size2, arr1[i]) &&
            !contains(result, count, arr1[i])) {
            result[count] = arr1[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    *result_size = count;
    return result;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 4, 5, 2};
    int arr2[] = {3, 4, 5, 6, 7, 4};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t result_size = 0;
    size_t i;
    int *result;

    result = find_intersection(arr1, size1, arr2, size2, &result_size);

    if (result == NULL) {
        printf("No intersection found or an error occurred.\n");
        return EXIT_FAILURE;
    }

    printf("Intersection: ");
    for (i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}