#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *key;
    int value;
} dict_entry;

int extract_unique_values(const dict_entry *dict, size_t size, int **unique_values, size_t *unique_count)
{
    if (unique_values == NULL || unique_count == NULL) {
        return -1;
    }
    *unique_values = NULL;
    *unique_count = 0;

    if (size == 0) {
        return 0;
    }
    if (dict == NULL) {
        return -1;
    }
    if (size > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    int *temp = malloc(size * sizeof(*temp));
    if (temp == NULL) {
        return -1;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        int current = dict[i].value;
        int found = 0;
        for (size_t j = 0; j < count; j++) {
            if (temp[j] == current) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[count] = current;
            count++;
        }
    }

    *unique_values = temp;
    *unique_count = count;
    return 0;
}

int main(void)
{
    dict_entry dictionary[] = {
        {"one", 10},
        {"two", 20},
        {"three", 10},
        {"four", 30},
        {"five", 20}
    };
    size_t dict_size = sizeof(dictionary) / sizeof(dictionary[0]);

    int *unique_values = NULL;
    size_t unique_count = 0;

    if (extract_unique_values(dictionary, dict_size, &unique_values, &unique_count) != 0) {
        fprintf(stderr, "Failed to extract unique values\n");
        return 1;
    }

    for (size_t i = 0; i < unique_count; i++) {
        printf("%d\n", unique_values[i]);
    }

    free(unique_values);
    return 0;
}