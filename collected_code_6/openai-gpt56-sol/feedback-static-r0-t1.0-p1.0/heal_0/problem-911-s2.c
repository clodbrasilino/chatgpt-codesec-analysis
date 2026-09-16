#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static void min_heapify(int *heap, size_t size, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left = index * 2U + 1U;
        size_t right = index * 2U + 2U;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        int temporary = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temporary;
        index = smallest;
    }
}

static void max_heapify(int *heap, size_t size, size_t index)
{
    for (;;) {
        size_t largest = index;
        size_t left = index * 2U + 1U;
        size_t right = index * 2U + 2U;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        int temporary = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temporary;
        index = largest;
    }
}

static int64_t maximum_product_of_three(const int *array, size_t length)
{
    int largest[3];
    int smallest[2];
    size_t largest_size = 0U;
    size_t smallest_size = 0U;

    for (size_t i = 0U; i < length; ++i) {
        int value = array[i];

        if (largest_size < 3U) {
            size_t position = largest_size++;
            largest[position] = value;

            while (position > 0U) {
                size_t parent = (position - 1U) / 2U;
                if (largest[parent] <= largest[position]) {
                    break;
                }

                int temporary = largest[parent];
                largest[parent] = largest[position];
                largest[position] = temporary;
                position = parent;
            }
        } else if (value > largest[0]) {
            largest[0] = value;
            min_heapify(largest, largest_size, 0U);
        }

        if (smallest_size < 2U) {
            size_t position = smallest_size++;
            smallest[position] = value;

            while (position > 0U) {
                size_t parent = (position - 1U) / 2U;
                if (smallest[parent] >= smallest[position]) {
                    break;
                }

                int temporary = smallest[parent];
                smallest[parent] = smallest[position];
                smallest[position] = temporary;
                position = parent;
            }
        } else if (value < smallest[0]) {
            smallest[0] = value;
            max_heapify(smallest, smallest_size, 0U);
        }
    }

    int64_t product_largest =
        (int64_t)largest[0] * (int64_t)largest[1] * (int64_t)largest[2];
    int64_t product_mixed =
        (int64_t)smallest[0] * (int64_t)smallest[1] * (int64_t)largest[0];

    return product_largest > product_mixed ? product_largest : product_mixed;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length < 3U ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result = maximum_product_of_three(array, length);
    printf("%" PRId64 "\n", result);

    free(array);
    return EXIT_SUCCESS;
}