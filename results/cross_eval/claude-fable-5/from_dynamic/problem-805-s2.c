#include <stdio.h>
#include <stdlib.h>

long long list_sum(const int *list, size_t length)
{
    long long sum = 0;
    size_t i;

    for (i = 0; i < length; i++) {
        sum += list[i];
    }

    return sum;
}

const int *find_max_sum_list(const int **lists, const size_t *lengths,
                             size_t num_lists, size_t *out_length)
{
    const int *best = NULL;
    long long best_sum = 0;
    size_t best_len = 0;
    size_t i;
    int found = 0;

    if (lists == NULL || lengths == NULL || out_length == NULL ||
        num_lists == 0) {
        if (out_length != NULL) {
            *out_length = 0;
        }
        return NULL;
    }

    for (i = 0; i < num_lists; i++) {
        long long current_sum;

        if (lists[i] == NULL) {
            continue;
        }

        current_sum = list_sum(lists[i], lengths[i]);

        if (found == 0 || current_sum > best_sum) {
            best = lists[i];
            best_sum = current_sum;
            best_len = lengths[i];
            found = 1;
        }
    }

    *out_length = best_len;
    return best;
}

int main(void)
{
    int list_a[] = { 1, 2, 3 };
    int list_b[] = { 10, 20, 30, 40 };
    int list_c[] = { -5, -10 };
    const int *lists[3];
    size_t lengths[3];
    const int *result;
    size_t result_length = 0;
    size_t i;

    lists[0] = list_a;
    lists[1] = list_b;
    lists[2] = list_c;

    lengths[0] = sizeof(list_a) / sizeof(list_a[0]);
    lengths[1] = sizeof(list_b) / sizeof(list_b[0]);
    lengths[2] = sizeof(list_c) / sizeof(list_c[0]);

    result = find_max_sum_list(lists, lengths, 3, &result_length);

    if (result == NULL) {
        if (fprintf(stderr, "No valid list found\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("List with highest sum: ") < 0) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_length; i++) {
        if (printf("%d ", result[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\nSum: %lld\n", list_sum(result, result_length)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}