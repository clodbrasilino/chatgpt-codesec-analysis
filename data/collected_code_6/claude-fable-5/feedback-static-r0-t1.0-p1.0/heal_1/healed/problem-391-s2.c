#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096U

typedef struct {
    char *key;
    int value;
} InnerDict;

typedef struct {
    char *key;
    InnerDict inner;
} NestedDict;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    copy = (char *)malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static void free_nested_dict(NestedDict *dict, size_t count)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        free(dict[i].key);
        free(dict[i].inner.key);
    }
    free(dict);
}

static NestedDict *convert_lists_to_nested_dict(const char *const *outer_keys,
                                                const char *const *inner_keys,
                                                const int *values,
                                                size_t count)
{
    NestedDict *dict;
    size_t i;

    if ((outer_keys == NULL) || (inner_keys == NULL) || (values == NULL) || (count == 0U)) {
        return NULL;
    }

    dict = (NestedDict *)calloc(count, sizeof(NestedDict));
    if (dict == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        dict[i].key = duplicate_string(outer_keys[i]);
        dict[i].inner.key = duplicate_string(inner_keys[i]);
        dict[i].inner.value = values[i];
        if ((dict[i].key == NULL) || (dict[i].inner.key == NULL)) {
            free_nested_dict(dict, count);
            return NULL;
        }
    }

    return dict;
}

static void print_nested_dict(const NestedDict *dict, size_t count)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    printf("[");
    for (i = 0U; i < count; i++) {
        printf("{'%s': {'%s': %d}}", dict[i].key, dict[i].inner.key, dict[i].inner.value);
        if (i < (count - 1U)) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    const char *student_ids[] = { "S001", "S002", "S003", "S004" };
    const char *student_names[] = { "Adina Park", "Leyton Marsh", "Duncan Boyle", "Saim Richards" };
    const int student_scores[] = { 85, 98, 89, 92 };
    const size_t count = sizeof(student_ids) / sizeof(student_ids[0]);
    NestedDict *dict;

    dict = convert_lists_to_nested_dict(student_ids, student_names, student_scores, count);
    if (dict == NULL) {
        fprintf(stderr, "Failed to build nested dictionary\n");
        return EXIT_FAILURE;
    }

    print_nested_dict(dict, count);
    free_nested_dict(dict, count);

    return EXIT_SUCCESS;
}