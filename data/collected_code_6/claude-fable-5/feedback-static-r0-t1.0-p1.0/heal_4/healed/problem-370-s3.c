#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 32
#define TUPLE_COUNT 5

typedef struct {
    char name[NAME_LEN];
    int id;
    float value;
} Tuple;

static int set_tuple_name(Tuple *t, const char *name)
{
    size_t len;

    if (t == NULL || name == NULL) {
        return -1;
    }
    len = strnlen(name, sizeof(t->name));
    if (len >= sizeof(t->name)) {
        return -1;
    }
    memcpy(t->name, name, len);
    t->name[len] = '\0';
    return 0;
}

static int init_tuple(Tuple *t, const char *name, int id, float value)
{
    if (t == NULL) {
        return -1;
    }
    if (set_tuple_name(t, name) != 0) {
        return -1;
    }
    t->id = id;
    t->value = value;
    return 0;
}

static int compare_by_float(const void *a, const void *b)
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

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return -1;
    }
    qsort(tuples, count, sizeof(Tuple), compare_by_float);
    return 0;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        (void)printf("(%.*s, %d, %.2f)\n",
                     NAME_LEN - 1,
                     tuples[i].name,
                     tuples[i].id,
                     (double)tuples[i].value);
    }
}

int main(void)
{
    Tuple tuples[TUPLE_COUNT];
    size_t i;
    static const char *const names[TUPLE_COUNT] = {
        "alpha", "beta", "gamma", "delta", "epsilon"
    };
    static const int ids[TUPLE_COUNT] = { 1, 2, 3, 4, 5 };
    static const float values[TUPLE_COUNT] = {
        3.14f, 1.41f, 2.72f, 0.58f, 1.62f
    };

    for (i = 0U; i < TUPLE_COUNT; i++) {
        if (init_tuple(&tuples[i], names[i], ids[i], values[i]) != 0) {
            (void)fprintf(stderr, "Error: failed to initialize tuple %zu\n", i);
            return EXIT_FAILURE;
        }
    }

    (void)printf("Before sorting:\n");
    print_tuples(tuples, TUPLE_COUNT);

    if (sort_tuples(tuples, TUPLE_COUNT) != 0) {
        (void)fprintf(stderr, "Error: failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    (void)printf("After sorting:\n");
    print_tuples(tuples, TUPLE_COUNT);

    return EXIT_SUCCESS;
}