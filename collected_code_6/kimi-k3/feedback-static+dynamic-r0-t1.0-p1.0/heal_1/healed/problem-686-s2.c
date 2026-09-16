#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

static size_t find_index(const Frequency *frequencies, size_t size, int value)
{
    size_t i;

    for (i = 0; i < size; ++i) {
        if (frequencies[i].value == value) {
            return i;
        }
    }
    return size;
}

int count_frequencies(const int *list, size_t list_size, Frequency **frequencies, size_t *frequency_count)
{
    Frequency *temp;
    size_t i;
    size_t size;
    size_t capacity;

    if (frequencies == NULL || frequency_count == NULL) {
        return 0;
    }
    if (list_size > 0 && list == NULL) {
        return 0;
    }

    *frequencies = NULL;
    *frequency_count = 0;

    if (list_size == 0) {
        return 1;
    }

    capacity = 8;
    temp = (Frequency *)malloc(capacity * sizeof(*temp));
    if (temp == NULL) {
        return 0;
    }

    size = 0;
    for (i = 0; i < list_size; ++i) {
        size_t index = find_index(temp, size, list[i]);
        if (index < size) {
            temp[index].count += 1;
        } else {
            if (size == capacity) {
                size_t new_capacity = capacity * 2;
                Frequency *new_temp = (Frequency *)realloc(temp, new_capacity * sizeof(*new_temp));
                if (new_temp == NULL) {
                    free(temp);
                    return 0;
                }
                temp = new_temp;
                capacity = new_capacity;
            }
            temp[size].value = list[i];
            temp[size].count = 1;
            ++size;
        }
    }

    *frequencies = temp;
    *frequency_count = size;
    return 1;
}

int main(void)
{
    int list[] = {4, 2, 4, 3, 2, 4, 5, 3, 4};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    Frequency *frequencies;
    size_t frequency_count;
    size_t i;

    frequencies = NULL;
    frequency_count = 0;

    if (!count_frequencies(list, list_size, &frequencies, &frequency_count)) {
        fprintf(stderr, "Failed to count frequencies.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < frequency_count; ++i) {
        printf("%d: %d\n", frequencies[i].value, frequencies[i].count);
    }

    free(frequencies);
    return EXIT_SUCCESS;
}