#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

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

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;
    int overflow = 0;

    if (buffer == NULL || capacity < 2) {
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

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            overflow = 1;
        }
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[length] = '\0';
    return !overflow;
}

static int read_uintmax_value(uintmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return 0;
    }

    if (token[0] == '-' || token[0] == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'errno'
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  use of undeclared identifier 'ERANGE'
     */
    if (errno == ERANGE || end == token || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !read_uintmax_value(&parsed)) {
        return 0;
    }

    if (parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int(int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return 0;
    }

    /* Possible weaknesses found:
     *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
     *  use of undeclared identifier 'errno'
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  use of undeclared identifier 'ERANGE'
     */
    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
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

    /* Possible weaknesses found:
     *  Assuming that condition 'k<count3' is not redundant
     *  Assuming that condition 'j<count2' is not redundant
     */
    while (i < count1 && j < count2 && k < count3) {
        int cmp12 = compare_pairs(&list1[i], &list2[j]);
        int cmp13 = compare_pairs(&list1[i], &list3[k]);

        if (cmp12 == 0 && cmp13 == 0) {
            Pair value = list1[i];
            size_t start1 = i;
            size_t start2 = j;
            size_t start3 = k;
            size_t common;

            while (i < count1 &&
                   compare_pairs(&list1[i], &value) == 0) {
                ++i;
            }
            while (j < count2 &&
                   compare_pairs(&list2[j], &value) == 0) {
                ++j;
            }
            while (k < count3 &&
                   compare_pairs(&list3[k], &value) == 0) {
                ++k;
            }

            common = i - start1;
            if (j - start2 < common) {
                common = j - start2;
            }
            if (k - start3 < common) {
                common = k - start3;
            }

            if (common > SIZE_MAX - matches) {
                return SIZE_MAX;
            }
            matches += common;
        } else {
            const Pair *minimum = &list1[i];

            if (compare_pairs(&list2[j], minimum) < 0) {
                minimum = &list2[j];
            }
            if (compare_pairs(&list3[k], minimum) < 0) {
                minimum = &list3[k];
            }

            if (compare_pairs(&list1[i], minimum) == 0) {
                Pair value = list1[i];
                while (i < count1 &&
                       compare_pairs(&list1[i], &value) == 0) {
                    ++i;
                }
            }
            /* Possible weaknesses found:
             *  Condition 'j<count2' is always true
             *  Condition 'j<count2' is always true [knownConditionTrueFalse]
             */
            if (j < count2 &&
                compare_pairs(&list2[j], minimum) == 0) {
                Pair value = list2[j];
                while (j < count2 &&
                       compare_pairs(&list2[j], &value) == 0) {
                    ++j;
                }
            }
            /* Possible weaknesses found:
             *  Condition 'k<count3' is always true
             *  Condition 'k<count3' is always true [knownConditionTrueFalse]
             */
            if (k < count3 &&
                compare_pairs(&list3[k], minimum) == 0) {
                Pair value = list3[k];
                while (k < count3 &&
                       compare_pairs(&list3[k], &value) == 0) {
                    ++k;
                }
            }
        }
    }

    return matches;
}

int main(void)
{
    size_t count1;
    size_t count2;
    size_t count3;
    Pair *list1 = NULL;
    Pair *list2 = NULL;
    Pair *list3 = NULL;
    size_t result;
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

    result = count_same_pairs(list1, count1, list2, count2,
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