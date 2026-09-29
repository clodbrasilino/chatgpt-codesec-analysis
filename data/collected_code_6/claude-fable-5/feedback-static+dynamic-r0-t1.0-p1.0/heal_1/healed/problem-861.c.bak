#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_chars(const void *a, const void *b)
{
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;
    return (ca > cb) - (ca < cb);
}

static char *sorted_copy(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strlen(s);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, len + 1);
    qsort(copy, len, sizeof(char), compare_chars);
    return copy;
}

int find_anagrams(const char *target, const char *const *list, size_t count,
                  size_t *indices, size_t *found_count)
{
    char *sorted_target;

    if (target == NULL || list == NULL || indices == NULL ||
        found_count == NULL) {
        return -1;
    }

    *found_count = 0;

    sorted_target = sorted_copy(target);
    if (sorted_target == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        char *sorted_candidate;

        if (list[i] == NULL) {
            continue;
        }

        if (strlen(list[i]) != strlen(target)) {
            continue;
        }

        sorted_candidate = sorted_copy(list[i]);
        if (sorted_candidate == NULL) {
            free(sorted_target);
            return -1;
        }

        if (strcmp(sorted_target, sorted_candidate) == 0) {
            indices[*found_count] = i;
            (*found_count)++;
        }

        free(sorted_candidate);
    }

    free(sorted_target);
    return 0;
}

int main(void)
{
    const char *target = "listen";
    const char *const words[] = {
        "enlist", "google", "inlets", "banana", "silent", "tinsel"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t *indices;
    size_t found_count = 0;
    int result;

    indices = malloc(count * sizeof(size_t));
    if (indices == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = find_anagrams(target, words, count, indices, &found_count);
    if (result != 0) {
        fprintf(stderr, "Error while searching for anagrams\n");
        free(indices);
        return EXIT_FAILURE;
    }

    if (found_count == 0) {
        printf("No anagrams of \"%s\" found.\n", target);
    } else {
        printf("Anagrams of \"%s\":\n", target);
        for (size_t i = 0; i < found_count; i++) {
            printf("  %s\n", words[indices[i]]);
        }
    }

    free(indices);
    return EXIT_SUCCESS;
}