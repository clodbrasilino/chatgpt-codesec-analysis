#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 32

typedef struct {
    int key;
    char value[MAX_NAME_LEN];
} Tuple;

static int tuple_set(Tuple *t, int key, const char *name)
{
    int written;

    if (t == NULL || name == NULL) {
        return -1;
    }

    t->key = key;
    written = snprintf(t->value, sizeof(t->value), "%s", name);
    if (written < 0 || (size_t)written >= sizeof(t->value)) {
        t->value[sizeof(t->value) - 1U] = '\0';
        return -1;
    }
    return 0;
}

static int tuple_copy_value(Tuple *dst, const Tuple *src)
{
    int written;

    if (dst == NULL || src == NULL) {
        return -1;
    }

    written = snprintf(dst->value, sizeof(dst->value), "%s", src->value);
    if (written < 0 || (size_t)written >= sizeof(dst->value)) {
        dst->value[sizeof(dst->value) - 1U] = '\0';
        return -1;
    }
    return 0;
}

static int sort_on_occurrence(const Tuple *input, size_t count, Tuple *output)
{
    size_t i;
    size_t j;
    size_t out_index;
    int *seen_keys;
    size_t seen_count;

    if (input == NULL || output == NULL || count == 0U) {
        return -1;
    }

    if (count > (size_t)-1 / sizeof(int)) {
        return -1;
    }

    seen_keys = (int *)malloc(count * sizeof(int));
    if (seen_keys == NULL) {
        return -1;
    }

    seen_count = 0U;
    out_index = 0U;

    for (i = 0U; i < count; i++) {
        int already_seen = 0;
        for (j = 0U; j < seen_count; j++) {
            if (seen_keys[j] == input[i].key) {
                already_seen = 1;
                break;
            }
        }
        if (already_seen == 0) {
            if (seen_count >= count) {
                free(seen_keys);
                return -1;
            }
            seen_keys[seen_count] = input[i].key;
            seen_count++;
            for (j = 0U; j < count; j++) {
                if (input[j].key == input[i].key) {
                    if (out_index >= count) {
                        free(seen_keys);
                        return -1;
                    }
                    output[out_index].key = input[j].key;
                    if (tuple_copy_value(&output[out_index], &input[j]) != 0) {
                        free(seen_keys);
                        return -1;
                    }
                    out_index++;
                }
            }
        }
    }

    free(seen_keys);
    return 0;
}

int main(void)
{
    Tuple data[6];
    size_t count = sizeof(data) / sizeof(data[0]);
    Tuple *sorted;
    size_t i;
    int result;

    if (tuple_set(&data[0], 1, "Jake") != 0 ||
        tuple_set(&data[1], 2, "Bob") != 0 ||
        tuple_set(&data[2], 1, "Cara") != 0 ||
        tuple_set(&data[3], 3, "Ann") != 0 ||
        tuple_set(&data[4], 2, "Dan") != 0 ||
        tuple_set(&data[5], 1, "Eli") != 0) {
        (void)fprintf(stderr, "Tuple initialization failed\n");
        return EXIT_FAILURE;
    }

    if (count > (size_t)-1 / sizeof(Tuple)) {
        (void)fprintf(stderr, "Count too large\n");
        return EXIT_FAILURE;
    }

    sorted = (Tuple *)malloc(count * sizeof(Tuple));
    if (sorted == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = sort_on_occurrence(data, count, sorted);
    if (result != 0) {
        (void)fprintf(stderr, "Sorting failed\n");
        free(sorted);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%d, %s)\n", sorted[i].key, sorted[i].value) < 0) {
            free(sorted);
            return EXIT_FAILURE;
        }
    }

    free(sorted);
    return EXIT_SUCCESS;
}