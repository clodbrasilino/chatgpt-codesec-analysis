#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>

static void min_heapify(int *heap, size_t size, size_t index)
{
    for (;;) {
        size_t smallest = index;

        if (index > (SIZE_MAX - 2U) / 2U) {
            break;
        }

        size_t left = index * 2U + 1U;
        size_t right = left + 1U;

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

        if (index > (SIZE_MAX - 2U) / 2U) {
            break;
        }

        size_t left = index * 2U + 1U;
        size_t right = left + 1U;

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

static int maximum_product_of_three(const int *array, size_t length,
                                    int64_t *result)
{
    if (array == NULL || result == NULL || length < 3U) {
        return 0;
    }

    int largest[3] = {0, 0, 0};
    int smallest[2] = {0, 0};
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

    if (largest_size != 3U || smallest_size != 2U) {
        return 0;
    }

    int64_t product_largest =
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 47303360945729 * 687778777 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000016,time:31256,execs:17179,op:havoc,rep:3)
         * UBSan: signed integer overflow: 59836666338 * 687777747 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:9765,execs:5875,op:havoc,rep:6)
         */
        (int64_t)largest[0] * largest[1] * largest[2];
    int64_t product_mixed =
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -14089589647 * -2012798521 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000010,time:40460,execs:22087,op:havoc,rep:5)
         */
        (int64_t)smallest[0] * smallest[1] * largest[0];

    *result = product_largest > product_mixed
                  ? product_largest
                  : product_mixed;

    return 1;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 ||
        length < 3U ||
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

    int64_t result;

    if (!maximum_product_of_three(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}