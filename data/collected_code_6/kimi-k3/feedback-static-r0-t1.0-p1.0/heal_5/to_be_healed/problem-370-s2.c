#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char label[32];
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;

    if (tuple_a->value < tuple_b->value) {
        return -1;
    }
    if (tuple_a->value > tuple_b->value) {
        return 1;
    }
    return 0;
}

static int set_label(Tuple *tuple, const char *label)
{
    size_t label_length;

    if (tuple == NULL || label == NULL) {
        return -1;
    }

    label_length = strnlen(label, sizeof(tuple->label));
    if (label_length >= sizeof(tuple->label)) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(tuple->label, label, sizeof(tuple->label) - 1U);
    tuple->label[sizeof(tuple->label) - 1U] = '\0';
    return 0;
}

int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return -1;
    }

    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 3.14f, ""},
        {2, 1.41f, ""},
        {3, 2.71f, ""},
        {4, 0.57f, ""},
        {5, 1.61f, ""}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (set_label(&tuples[0], "Pi") != 0 ||
        set_label(&tuples[1], "Sqrt2") != 0 ||
        set_label(&tuples[2], "Euler") != 0 ||
        set_label(&tuples[3], "Gamma") != 0 ||
        set_label(&tuples[4], "Golden") != 0) {
        fprintf(stderr, "Failed to initialize tuple labels\n");
        return EXIT_FAILURE;
    }

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        printf("ID: %d, Value: %.2f, Label: %s\n",
               tuples[i].id, tuples[i].value, tuples[i].label);
    }

    return EXIT_SUCCESS;
}