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
    int written;

    if (tuple == NULL || name == NULL) {
        return -1;
    }

    len = strnlen(name, sizeof(tuple->name));
    if (len >= sizeof(tuple->name)) {
        return -1;
    }

    written = snprintf(tuple->name, sizeof(tuple->name), "%s", name);
    if (written < 0 || (size_t)written >= sizeof(tuple->name)) {
        return -1;
    }
    return 0;
}

static int init_tuple(Tuple *tuple, const char *name, float value)
{
    if (tuple == NULL) {
        return -1;
    }

    if (set_tuple_name(tuple, name) != 0) {
        return -1;
    }
    tuple->value = value;
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
    size_t i;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *const names[TUPLE_COUNT] = { "alpha", "beta", "gamma", "delta", "epsilon" };
    const float values[TUPLE_COUNT] = { 3.14f, 1.41f, 2.72f, 0.58f, 1.62f };

    memset(tuples, 0, sizeof(tuples));

    for (i = 0U; i < TUPLE_COUNT; i++) {
        if (init_tuple(&tuples[i], names[i], values[i]) != 0) {
            (void)fprintf(stderr, "Failed to initialize tuple %zu\n", i);
            return EXIT_FAILURE;
        }
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