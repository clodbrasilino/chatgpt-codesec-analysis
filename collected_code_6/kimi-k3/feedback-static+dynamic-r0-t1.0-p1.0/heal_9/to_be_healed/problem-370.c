#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define NAME_SIZE 32

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_SIZE];
    float value;
} Tuple;

static int copy_name(char *dest, size_t dest_size, const char *src) {
    size_t len;

    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    len = strnlen(src, dest_size - 1);
    if (len >= dest_size - 1 && src[len] != '\0') {
        return -1;
    }

    if (len > 0) {
        if (len >= dest_size) {
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, len);
    }
    dest[len] = '\0';
    return 0;
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->value < tb->value) return -1;
    if (ta->value > tb->value) return 1;
    return 0;
}

int sort_tuples_by_float(Tuple *arr, size_t count) {
    if (arr == NULL || count == 0) {
        return -1;
    }
    qsort(arr, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void) {
    Tuple data[] = {
        {1, "", 3.14f},
        {2, "", 1.41f},
        {3, "", 2.72f},
        {4, "", 0.58f}
    };
    const char *names[] = {"alpha", "beta", "gamma", "delta"};
    size_t count = sizeof(data) / sizeof(data[0]);

    for (size_t i = 0; i < count; i++) {
        if (copy_name(data[i].name, sizeof(data[i].name), names[i]) != 0) {
            fprintf(stderr, "Error: Name too long\n");
            return EXIT_FAILURE;
        }
    }

    if (sort_tuples_by_float(data, count) != 0) {
        fprintf(stderr, "Error: Invalid input to sort function\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Value: %.2f\n",
               data[i].id, data[i].name, (double)data[i].value);
    }

    return EXIT_SUCCESS;
}