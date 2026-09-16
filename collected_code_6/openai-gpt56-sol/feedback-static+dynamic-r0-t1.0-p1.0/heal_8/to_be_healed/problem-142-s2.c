#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_pairs(const void *lhs, const void *rhs)
{
    const Pair *left = lhs;
    const Pair *right = rhs;

    if (left->first < right->first) {
        return -1;
    }
    if (left->first > right->first) {
        return 1;
    }
    if (left->second < right->second) {
        return -1;
    }
    if (left->second > right->second) {
        return 1;
    }

    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

static size_t count_same_pairs(Pair *list1, size_t count1,
                               Pair *list2, size_t count2,
                               Pair *list3, size_t count3)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t matches = 0;

    qsort(list1, count1, sizeof(*list1), compare_pairs);
    qsort(list2, count2, sizeof(*list2), compare_pairs);
    qsort(list3, count3, sizeof(*list3), compare_pairs);

    while (i < count1 && j < count2 && k < count3) {
        int cmp12 = compare_pairs(&list1[i], &list2[j]);
        int cmp13 = compare_pairs(&list1[i], &list3[k]);

        if (cmp12 == 0 && cmp13 == 0) {
            Pair value = list1[i];
            size_t occurrences1 = 0;
            size_t occurrences2 = 0;
            size_t occurrences3 = 0;
            size_t common;

            while (i < count1 &&
                   compare_pairs(&list1[i], &value) == 0) {
                ++i;
                ++occurrences1;
            }

            while (j < count2 &&
                   compare_pairs(&list2[j], &value) == 0) {
                ++j;
                ++occurrences2;
            }

            while (k < count3 &&
                   compare_pairs(&list3[k], &value) == 0) {
                ++k;
                ++occurrences3;
            }

            common = occurrences1;
            if (occurrences2 < common) {
                common = occurrences2;
            }
            if (occurrences3 < common) {
                common = occurrences3;
            }

            if (common > SIZE_MAX - matches) {
                return SIZE_MAX;
            }

            matches += common;
        } else {
            Pair smallest = list1[i];

            if (compare_pairs(&list2[j], &smallest) < 0) {
                smallest = list2[j];
            }
            if (compare_pairs(&list3[k], &smallest) < 0) {
                smallest = list3[k];
            }

            while (i < count1 &&
                   compare_pairs(&list1[i], &smallest) == 0) {
                ++i;
            }
            while (j < count2 &&
                   compare_pairs(&list2[j], &smallest) == 0) {
                ++j;
            }
            while (k < count3 &&
                   compare_pairs(&list3[k], &smallest) == 0) {
                ++k;
            }
        }
    }

    return matches;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || scanf("%127s", buffer) != 1) {
        return 0;
    }

    if (buffer[0] == '-' || buffer[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_pairs(Pair *list, size_t count)
{
    if (count != 0 && list == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d %d", &list[i].first, &list[i].second) != 2) {
            return 0;
        }
    }

    return 1;
}

static Pair *allocate_pairs(size_t count)
{
    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(Pair)) {
        return NULL;
    }

    return malloc(count * sizeof(Pair));
}

int main(void)
{
    size_t count1;
    size_t count2;
    size_t count3;
    Pair *list1 = NULL;
    Pair *list2 = NULL;
    Pair *list3 = NULL;
    int status = EXIT_FAILURE;

    if (!read_size(&count1)) {
        goto cleanup;
    }

    list1 = allocate_pairs(count1);
    if (count1 != 0 && list1 == NULL) {
        goto cleanup;
    }

    if (!read_pairs(list1, count1)) {
        goto cleanup;
    }

    if (!read_size(&count2)) {
        goto cleanup;
    }

    list2 = allocate_pairs(count2);
    if (count2 != 0 && list2 == NULL) {
        goto cleanup;
    }

    if (!read_pairs(list2, count2)) {
        goto cleanup;
    }

    if (!read_size(&count3)) {
        goto cleanup;
    }

    list3 = allocate_pairs(count3);
    if (count3 != 0 && list3 == NULL) {
        goto cleanup;
    }

    if (!read_pairs(list3, count3)) {
        goto cleanup;
    }

    printf("%zu\n", count_same_pairs(list1, count1,
                                     list2, count2,
                                     list3, count3));
    status = EXIT_SUCCESS;

cleanup:
    free(list1);
    free(list2);
    free(list3);
    return status;
}