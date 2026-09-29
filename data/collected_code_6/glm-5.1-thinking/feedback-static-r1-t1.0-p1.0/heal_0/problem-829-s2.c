#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Frequency {
    const char *str;
    size_t count;
};

const char *find_second_most_repeated(const char **arr, size_t n) {
    if (arr == NULL || n < 2) {
        return NULL;
    }

    struct Frequency *freqs = malloc(n * sizeof(struct Frequency));
    if (freqs == NULL) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < n; ++i) {
        if (arr[i] == NULL) {
            free(freqs);
            return NULL;
        }

        size_t j;
        for (j = 0; j < unique_count; ++j) {
            if (strcmp(arr[i], freqs[j].str) == 0) {
                freqs[j].count++;
                break;
            }
        }

        if (j == unique_count) {
            freqs[unique_count].str = arr[i];
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    if (unique_count < 2) {
        free(freqs);
        return NULL;
    }

    size_t max_count = 0;
    size_t second_max_count = 0;

    for (size_t i = 0; i < unique_count; ++i) {
        if (freqs[i].count > max_count) {
            max_count = freqs[i].count;
        }
    }

    for (size_t i = 0; i < unique_count; ++i) {
        if (freqs[i].count < max_count && freqs[i].count > second_max_count) {
            second_max_count = freqs[i].count;
        }
    }

    const char *result = NULL;

    if (second_max_count > 0) {
        for (size_t i = 0; i < unique_count; ++i) {
            if (freqs[i].count == second_max_count) {
                result = freqs[i].str;
                break;
            }
        }
    }

    free(freqs);
    return result;
}

int main(void) {
    const char *arr1[] = {"apple", "banana", "apple", "orange", "banana", "apple", "banana"};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    const char *res1 = find_second_most_repeated(arr1, n1);
    if (res1 != NULL) {
        printf("%s\n", res1);
    } else {
        printf("NULL\n");
    }

    const char *arr2[] = {"one", "one", "one"};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    const char *res2 = find_second_most_repeated(arr2, n2);
    if (res2 != NULL) {
        printf("%s\n", res2);
    } else {
        printf("NULL\n");
    }

    const char *arr3[] = {"a", "b", "c", "d"};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    const char *res3 = find_second_most_repeated(arr3, n3);
    if (res3 != NULL) {
        printf("%s\n", res3);
    } else {
        printf("NULL\n");
    }

    return 0;
}