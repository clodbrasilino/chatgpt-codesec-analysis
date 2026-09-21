#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_pairs(const void *lhs, const void *rhs)
{
    const Pair *left = lhs;
    const Pair *right = rhs;

    if (left->first != right->first) {
        return left->first < right->first ? -1 : 1;
    }

    if (left->second != right->second) {
        return left->second < right->second ? -1 : 1;
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
    qsort(list1, count1, sizeof(*list1), compare_pairs);
    qsort(list2, count2, sizeof(*list2), compare_pairs);
    qsort(list3, count3, sizeof(*list3), compare_pairs);

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t matches = 0;

    while (i < count1 && j < count2 && k < count3) {
        int cmp12 = compare_pairs(&list1[i], &list2[j]);
        int cmp13 = compare_pairs(&list1[i], &list3[k]);
        int cmp23 = compare_pairs(&list2[j], &list3[k]);

        if (cmp12 == 0 && cmp13 == 0) {
            Pair value = list1[i];
            size_t occurrences1 = 0;
            size_t occurrences2 = 0;
            size_t occurrences3 = 0;

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

            size_t common = occurrences1;

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
        } else if (cmp12 <= 0 && cmp13 <= 0) {
            ++i;
        } else if (cmp12 >= 0 && cmp23 <= 0) {
            ++j;
        } else {
            ++k;
        }
    }

    return matches;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;
    int ch;

    if (value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    if (ch == '-') {
        return 0;
    }

    if (ch == '+') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    }

    if (!isdigit((unsigned char)ch)) {
        return 0;
    }

    parsed = 0;

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (parsed > (UINTMAX_MAX - digit) / 10U) {
            return 0;
        }

        parsed = parsed * 10U + digit;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isdigit((unsigned char)ch));

    if (ch != EOF && !isspace((unsigned char)ch)) {
        return 0;
    }

    if (parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int(int *value)
{
    int ch;
    int negative = 0;
    uintmax_t parsed = 0;
    uintmax_t limit;

    if (value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    if (ch == '-' || ch == '+') {
        negative = ch == '-';
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == EOF) {
            return 0;
        }
    }

    if (!isdigit((unsigned char)ch)) {
        return 0;
    }

    limit = negative ? (uintmax_t)INT_MAX + 1U : (uintmax_t)INT_MAX;

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (parsed > (limit - digit) / 10U) {
            return 0;
        }

        parsed = parsed * 10U + digit;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isdigit((unsigned char)ch));

    if (ch != EOF && !isspace((unsigned char)ch)) {
        return 0;
    }

    if (negative) {
        if (parsed == (uintmax_t)INT_MAX + 1U) {
            *value = INT_MIN;
        } else {
            *value = -(int)parsed;
        }
    } else {
        *value = (int)parsed;
    }

    return 1;
}

static int read_pairs(Pair *list, size_t count)
{
    if (count != 0 && list == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int(&list[i].first) ||
            !read_int(&list[i].second)) {
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

    if (!read_size(&count1) ||
        !read_size(&count2) ||
        !read_size(&count3)) {
        goto cleanup;
    }

    list1 = allocate_pairs(count1);
    list2 = allocate_pairs(count2);
    list3 = allocate_pairs(count3);

    if ((count1 != 0 && list1 == NULL) ||
        (count2 != 0 && list2 == NULL) ||
        (count3 != 0 && list3 == NULL)) {
        goto cleanup;
    }

    if (!read_pairs(list1, count1) ||
        !read_pairs(list2, count2) ||
        !read_pairs(list3, count3)) {
        goto cleanup;
    }

    size_t result = count_same_pairs(list1, count1, list2, count2,
                                     list3, count3);

    if (printf("%zu\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(list1);
    free(list2);
    free(list3);
    return status;
}