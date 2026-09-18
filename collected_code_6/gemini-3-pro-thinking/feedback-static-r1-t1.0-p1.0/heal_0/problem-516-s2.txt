#include <stdio.h>
#include <stdlib.h>

int get_max(const int *array, size_t size);
int counting_sort(int *array, size_t size, long long place);
int radix_sort(int *array, size_t size);
void print_array(const int *array, size_t size);

int get_max(const int *array, size_t size) {
    int max = array[0];
    for (size_t i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int counting_sort(int *array, size_t size, long long place) {
    if (size == 0) {
        return 0;
    }

    int *output = (int *)malloc(size * sizeof(int));
    if (output == NULL) {
        return -1;
    }

    int count[10] = {0};

    for (size_t i = 0; i < size; i++) {
        count[(array[i] / place) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (size_t i = size; i > 0; i--) {
        output[count[(array[i - 1] / place) % 10] - 1] = array[i - 1];
        count[(array[i - 1] / place) % 10]--;
    }

    for (size_t i = 0; i < size; i++) {
        array[i] = output[i];
    }

    free(output);
    return 0;
}

int radix_sort(int *array, size_t size) {
    if (array == NULL || size <= 1) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        if (array[i] < 0) {
            return -1;
        }
    }

    int max = get_max(array, size);

    for (long long place = 1; max / place > 0; place *= 10) {
        if (counting_sort(array, size, place) != 0) {
            return -1;
        }
    }

    return 0;
}

void print_array(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) {
    int array[] = {170, 45, 75, 90, 802, 24, 2, 66};
    size_t size = sizeof(array) / sizeof(array[0]);

    if (radix_sort(array, size) != 0) {
        fprintf(stderr, "Error: Radix sort failed.\n");
        return EXIT_FAILURE;
    }

    print_array(array, size);

    return EXIT_SUCCESS;
}