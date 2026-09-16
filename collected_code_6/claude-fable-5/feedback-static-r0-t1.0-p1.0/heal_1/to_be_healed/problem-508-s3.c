#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t len, int value)
{
    size_t i;

    for (i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

static int *extract_common(const int *a, size_t a_len,
                           const int *b, size_t b_len,
                           size_t *out_len)
{
    int *result;
    size_t i;
    size_t count = 0;

    if (out_len == NULL) {
        return NULL;
    }
    *out_len = 0;

    if (a == NULL || b == NULL || a_len == 0 || b_len == 0) {
        return NULL;
    }

    result = malloc(a_len * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < a_len; i++) {
        if (contains(b, b_len, a[i])) {
            result[count] = a[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    *out_len = count;
    return result;
}

bool same_order(const int *a, size_t a_len, const int *b, size_t b_len)
{
    int *common_a;
    int *common_b;
    size_t len_a = 0;
    size_t len_b = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    bool result = true;

    common_a = extract_common(a, a_len, b, b_len, &len_a);
    common_b = extract_common(b, b_len, a, a_len, &len_b);

    if (common_a == NULL || common_b == NULL) {
        free(common_a);
        free(common_b);
        return (len_a == 0 && len_b == 0);
    }

    if (len_a != len_b) {
        result = false;
    } else {
        for (i = 0; i < len_a; i++) {
            if (common_a[i] != common_b[i]) {
                result = false;
                break;
            }
        }
    }

    free(common_a);
    free(common_b);
    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 7, 9};
    int list2[] = {9, 2, 3, 7};
    int list3[] = {2, 3, 7, 9};
    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t len3 = sizeof(list3) / sizeof(list3[0]);

    if (same_order(list1, len1, list2, len2)) {
        printf("Common elements are in the same order\n");
    } else {
        printf("Common elements are not in the same order\n");
    }

    if (same_order(list1, len1, list3, len3)) {
        printf("Common elements are in the same order\n");
    } else {
        printf("Common elements are not in the same order\n");
    }

    return EXIT_SUCCESS;
}