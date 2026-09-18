#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>

static void swap_int(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void min_heap_sift_up(int heap[], size_t index)
{
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (heap[parent] <= heap[index]) {
            break;
        }

        swap_int(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void max_heap_sift_up(int heap[], size_t index)
{
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (heap[parent] >= heap[index]) {
            break;
        }

        swap_int(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void min_heap_replace_root(int heap[], size_t size, int value)
{
    size_t index = 0U;

    heap[0] = value;

    for (;;) {
        size_t left;
        size_t right;
        size_t smallest = index;

        if (index > (size - 1U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        right = left + 1U;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_int(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static void max_heap_replace_root(int heap[], size_t size, int value)
{
    size_t index = 0U;

    heap[0] = value;

    for (;;) {
        size_t left;
        size_t right;
        size_t largest = index;

        if (index > (size - 1U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        right = left + 1U;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        swap_int(&heap[index], &heap[largest]);
        index = largest;
    }
}

static int multiply_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if (a > 0) {
        if (b > 0) {
            if (a > INT64_MAX / b) {
                return -1;
            }
        } else if (b < 0) {
            if (b < INT64_MIN / a) {
                return -1;
            }
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < INT64_MIN / b) {
                return -1;
            }
        } else if (b < 0) {
            if (a < INT64_MAX / b) {
                return -1;
            }
        }
    }

    *result = a * b;
    return 0;
}

static int product_of_three(int a, int b, int c, int64_t *result)
{
    int64_t partial;

    if (multiply_int64((int64_t)a, (int64_t)b, &partial) != 0) {
        return -1;
    }

    return multiply_int64(partial, (int64_t)c, result);
}

static int maximum_product_of_three(const int array[], size_t length,
                                    int64_t *result)
{
    int largest[3] = {0, 0, 0};
    int smallest[2] = {0, 0};
    size_t largest_size = 0U;
    size_t smallest_size = 0U;
    int largest_value;
    int64_t product_largest;
    int64_t product_mixed;

    if (array == NULL || result == NULL || length < 3U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        int value = array[i];

        if (largest_size < 3U) {
            largest[largest_size] = value;
            min_heap_sift_up(largest, largest_size);
            ++largest_size;
        } else if (value > largest[0]) {
            min_heap_replace_root(largest, largest_size, value);
        }

        if (smallest_size < 2U) {
            smallest[smallest_size] = value;
            max_heap_sift_up(smallest, smallest_size);
            ++smallest_size;
        } else if (value < smallest[0]) {
            max_heap_replace_root(smallest, smallest_size, value);
        }
    }

    largest_value = largest[0];

    if (largest[1] > largest_value) {
        largest_value = largest[1];
    }

    if (largest[2] > largest_value) {
        largest_value = largest[2];
    }

    if (product_of_three(largest[0], largest[1], largest[2],
                         &product_largest) != 0 ||
        product_of_three(smallest[0], smallest[1], largest_value,
                         &product_mixed) != 0) {
        return -1;
    }

    *result = product_largest > product_mixed
                  ? product_largest
                  : product_mixed;

    return 0;
}

int main(void)
{
    size_t length;
    int *array;
    int64_t result;

    if (scanf("%zu", &length) != 1 ||
        length < 3U ||
        length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (maximum_product_of_three(array, length, &result) != 0) {
        fprintf(stderr, "Unable to compute maximum product\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);

    return EXIT_SUCCESS;
}