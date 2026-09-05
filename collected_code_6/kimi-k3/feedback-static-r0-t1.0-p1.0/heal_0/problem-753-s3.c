#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Tuple;

int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->value < tb->value) return -1;
    if (ta->value > tb->value) return 1;
    return 0;
}

int find_min_k_records(const Tuple *list, size_t count, size_t k, Tuple *result)
{
    Tuple *temp;
    size_t i;

    if (list == NULL || result == NULL || k == 0 || k > count) {
        return -1;
    }

    temp = (Tuple *)malloc(count * sizeof(Tuple));
    if (temp == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        temp[i] = list[i];
    }

    qsort(temp, count, sizeof(Tuple), compare_tuples);

    for (i = 0; i < k; i++) {
        result[i] = temp[i];
    }

    free(temp);
    temp = NULL;

    return 0;
}

int main(void)
{
    Tuple list[] = {
        {1, 50},
        {2, 20},
        {3, 80},
        {4, 10},
        {5, 40},
        {6, 30}
    };
    size_t count = sizeof(list) / sizeof(list[0]);
    size_t k = 3;
    Tuple *result;
    size_t i;
    int status;

    result = (Tuple *)malloc(k * sizeof(Tuple));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = find_min_k_records(list, count, k, result);
    if (status != 0) {
        fprintf(stderr, "Error finding minimum k records\n");
        free(result);
        result = NULL;
        return EXIT_FAILURE;
    }

    printf("Minimum %zu records:\n", k);
    for (i = 0; i < k; i++) {
        printf("ID: %d, Value: %d\n", result[i].id, result[i].value);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}