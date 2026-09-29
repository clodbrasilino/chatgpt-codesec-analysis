#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_uintmax_value(uintmax_t *value)
{
    char *token;
    char *end;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    valid = token[0] != '\0' &&
            token[0] != '-' &&
            token[0] != '+';

    if (valid) {
        errno = 0;
        parsed = strtoumax(token, &end, 10);
        valid = errno != ERANGE && end != token && *end == '\0';
    }

    if (valid) {
        *value = parsed;
    }

    free(token);
    return valid;
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
    char *token;
    char *end;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    valid = errno != ERANGE &&
            end != token &&
            *end == '\0' &&
            parsed >= INT_MIN &&
            parsed <= INT_MAX;

    if (valid) {
        *value = (int)parsed;
    }

    free(token);
    return valid;
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

static int read_pairs(Pair *list, size_t count)
{
    size_t i;

    if (count != 0 && list == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (!read_int(&list[i].first) ||
            !read_int(&list[i].second)) {
            return 0;
        }
    }

    return 1;
}

static size_t advance_equal_pairs(const Pair *list, size_t count,
                                  size_t index)
{
    Pair value;

    if (list == NULL || index >= count) {
        return index;
    }

    value = list[index];

    do {
        ++index;
    } while (index < count &&
             compare_pairs(&list[index], &value) == 0);

    return index;
}

static size_t count_same_pairs(Pair *list1, size_t count1,
                               Pair *list2, size_t count2,
                               Pair *list3, size_t count3)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t matches = 0;

    if (count1 == 0 || count2 == 0 || count3 == 0) {
        return 0;
    }

    qsort(list1, count1, sizeof(*list1), compare_pairs);
    qsort(list2, count2, sizeof(*list2), compare_pairs);
    qsort(list3, count3, sizeof(*list3), compare_pairs);

    while (i < count1 && j < count2 && k < count3) {
        int cmp12 = compare_pairs(&list1[i], &list2[j]);
        int cmp13 = compare_pairs(&list1[i], &list3[k]);

        if (cmp12 == 0 && cmp13 == 0) {
            size_t next1 = advance_equal_pairs(list1, count1, i);
            size_t next2 = advance_equal_pairs(list2, count2, j);
            size_t next3 = advance_equal_pairs(list3, count3, k);
            size_t common = next1 - i;

            if (next2 - j < common) {
                common = next2 - j;
            }
            if (next3 - k < common) {
                common = next3 - k;
            }

            if (common > SIZE_MAX - matches) {
                return SIZE_MAX;
            }

            matches += common;
            i = next1;
            j = next2;
            k = next3;
        } else if (compare_pairs(&list1[i], &list2[j]) < 0 ||
                   compare_pairs(&list1[i], &list3[k]) < 0) {
            i = advance_equal_pairs(list1, count1, i);
        } else if (compare_pairs(&list2[j], &list1[i]) < 0 ||
                   compare_pairs(&list2[j], &list3[k]) < 0) {
            j = advance_equal_pairs(list2, count2, j);
        } else {
            k = advance_equal_pairs(list3, count3, k);
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

    result = count_same_pairs(list1, count1,
                              list2, count2,
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