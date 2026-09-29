#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_COUNT 5
#define NAME_LEN 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_LEN];
    float value;
} Tuple;

static int set_tuple_name(Tuple *tuple, const char *name)
{
    size_t len;

    if (tuple == NULL || name == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(name);
    if (len >= NAME_LEN) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->name, name, len);
    tuple->name[len] = '\0';
    return 0;
}

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->value < tb->value) {
        return -1;
    }
    if (ta->value > tb->value) {
        return 1;
    }
    return 0;
}

static void sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%.*s, %.2f)\n", NAME_LEN - 1, tuples[i].name,
                   (double)tuples[i].value) < 0) {
            break;
        }
    }
}

int main(void)
{
    Tuple tuples[TUPLE_COUNT];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *names[TUPLE_COUNT] = { "alpha", "beta", "gamma", "delta", "epsilon" };
    const float values[TUPLE_COUNT] = { 3.14f, 1.41f, 2.72f, 0.58f, 1.62f };
    size_t i;

    memset(tuples, 0, sizeof(tuples));

    for (i = 0U; i < TUPLE_COUNT; i++) {
        if (set_tuple_name(&tuples[i], names[i]) != 0) {
            return EXIT_FAILURE;
        }
        tuples[i].value = values[i];
    }

    if (printf("Before sorting:\n") < 0) {
        return EXIT_FAILURE;
    }
    print_tuples(tuples, TUPLE_COUNT);

    sort_tuples(tuples, TUPLE_COUNT);

    if (printf("After sorting:\n") < 0) {
        return EXIT_FAILURE;
    }
    print_tuples(tuples, TUPLE_COUNT);

    return EXIT_SUCCESS;
}