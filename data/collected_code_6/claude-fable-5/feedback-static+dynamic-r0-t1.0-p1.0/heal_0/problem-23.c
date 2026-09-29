#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long list_sum(const int *list, size_t length)
{
    long long sum = 0;
    size_t i;

    for (i = 0; i < length; i++) {
        sum += list[i];
    }

    return sum;
}

int max_list_sum(const int **lists, const size_t *lengths, size_t count, long long *result)
{
    long long max_sum;
    long long current;
    size_t i;

    if (lists == NULL || lengths == NULL || result == NULL || count == 0) {
        return -1;
    }

    max_sum = LLONG_MIN;

    for (i = 0; i < count; i++) {
        if (lists[i] == NULL && lengths[i] > 0) {
            return -1;
        }
        current = list_sum(lists[i], lengths[i]);
        if (current > max_sum) {
            max_sum = current;
        }
    }

    *result = max_sum;
    return 0;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4};
    int list2[] = {10, 20, 30};
    int list3[] = {-5, -10, 100};
    const int *lists[3];
    size_t lengths[3];
    long long result;
    int status;

    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;
    lengths[0] = sizeof(list1) / sizeof(list1[0]);
    lengths[1] = sizeof(list2) / sizeof(list2[0]);
    lengths[2] = sizeof(list3) / sizeof(list3[0]);

    status = max_list_sum(lists, lengths, 3, &result);
    if (status != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Maximum sum: %lld\n", result);
    return EXIT_SUCCESS;
}