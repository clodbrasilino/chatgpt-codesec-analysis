#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 32

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_SIZE];
    float value;
} Tuple;

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int copy_name(char dest[NAME_SIZE], const char *src) {
    size_t len;

    if (dest == NULL || src == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src);
    if (len >= NAME_SIZE) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, len + 1);
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
    /* Possible weaknesses found:
     *  expected ']'
     *  expected ',' or ';' before ']' token
     *  to match this '['
     *  Unmatched '['. Configuration: ''. [syntaxError]
     *  expected ']' before ')' token
     */
    size_t count = sizeof(data) / sizeof(data[0)];

    for (size_t i = 0; i < count; i++) {
        if (copy_name(data[i].name, names[i]) != 0) {
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