#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Triple {
    int a;
    int b;
    int c;
    int valid;
};

static long long absll(long long x)
{
    return (x < 0) ? -x : x;
}

static struct Triple find_closest(const int *arr1, size_t n1,
                                  const int *arr2, size_t n2,
                                  const int *arr3, size_t n3)
{
    struct Triple result;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    long long best_diff = LLONG_MAX;

    result.a = 0;
    result.b = 0;
    result.c = 0;
    result.valid = 0;

    if (arr1 == NULL || arr2 == NULL || arr3 == NULL) {
        return result;
    }
    if (n1 == 0 || n2 == 0 || n3 == 0) {
        return result;
    }

    while (i < n1 && j < n2 && k < n3) {
        long long x = arr1[i];
        long long y = arr2[j];
        long long z = arr3[k];
        long long minimum = x;
        long long maximum = x;
        long long diff;

        if (y < minimum) {
            minimum = y;
        }
        if (z < minimum) {
            minimum = z;
        }
        if (y > maximum) {
            maximum = y;
        }
        if (z > maximum) {
            maximum = z;
        }

        diff = absll(maximum - minimum);

        if (diff < best_diff) {
            best_diff = diff;
            result.a = arr1[i];
            result.b = arr2[j];
            result.c = arr3[k];
            result.valid = 1;
        }

        if (best_diff == 0) {
            break;
        }

        if (x == minimum) {
            i++;
        } else if (y == minimum) {
            j++;
        } else {
            k++;
        }
    }

    return result;
}

int main(void)
{
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    struct Triple t;

    t = find_closest(arr1, n1, arr2, n2, arr3, n3);

    if (t.valid == 0) {
        if (fprintf(stderr, "No valid triple found\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Closest elements: %d %d %d\n", t.a, t.b, t.c) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}