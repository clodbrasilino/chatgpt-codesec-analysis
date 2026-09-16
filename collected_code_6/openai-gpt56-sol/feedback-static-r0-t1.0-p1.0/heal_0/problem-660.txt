#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t count;
} PointSet;

static int choose_points(int start1, int end1, int start2, int end2,
                         PointSet *first, PointSet *second)
{
    size_t count1;
    size_t count2;
    int *values1 = NULL;
    int *values2 = NULL;
    size_t index1 = 0;
    size_t index2 = 0;
    long long point;

    if (first == NULL || second == NULL || start1 > end1 || start2 > end2) {
        return 0;
    }

    first->values = NULL;
    first->count = 0;
    second->values = NULL;
    second->count = 0;

    count1 = (size_t)((long long)end1 - start1 + 1);
    count2 = (size_t)((long long)end2 - start2 + 1);

    if (count1 > SIZE_MAX / sizeof(*values1) ||
        count2 > SIZE_MAX / sizeof(*values2)) {
        return 0;
    }

    values1 = malloc(count1 * sizeof(*values1));
    values2 = malloc(count2 * sizeof(*values2));

    if (values1 == NULL || values2 == NULL) {
        free(values1);
        free(values2);
        return 0;
    }

    for (point = start1; point <= end1; ++point) {
        if (point < start2 || point > end2) {
            values1[index1++] = (int)point;
        }
    }

    for (point = start2; point <= end2; ++point) {
        if (point < start1 || point > end1) {
            values2[index2++] = (int)point;
        }
    }

    first->values = values1;
    first->count = index1;
    second->values = values2;
    second->count = index2;

    return 1;
}

static void free_point_set(PointSet *set)
{
    if (set != NULL) {
        free(set->values);
        set->values = NULL;
        set->count = 0;
    }
}

static void print_point_set(const PointSet *set)
{
    size_t i;

    if (set == NULL) {
        return;
    }

    for (i = 0; i < set->count; ++i) {
        printf("%d%s", set->values[i], i + 1 == set->count ? "\n" : " ");
    }

    if (set->count == 0) {
        putchar('\n');
    }
}

int main(void)
{
    int start1;
    int end1;
    int start2;
    int end2;
    PointSet first = {NULL, 0};
    PointSet second = {NULL, 0};

    if (scanf("%d %d %d %d", &start1, &end1, &start2, &end2) != 4) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!choose_points(start1, end1, start2, end2, &first, &second)) {
        fprintf(stderr, "Unable to choose points\n");
        return EXIT_FAILURE;
    }

    print_point_set(&first);
    print_point_set(&second);

    free_point_set(&first);
    free_point_set(&second);

    return EXIT_SUCCESS;
}