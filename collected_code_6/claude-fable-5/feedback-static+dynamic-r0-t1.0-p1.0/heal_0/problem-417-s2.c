#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int first;
    int *seconds;
    size_t count;
} Group;

static int group_by_first(const Tuple *tuples, size_t n, Group **out_groups, size_t *out_count)
{
    Group *groups;
    size_t group_count;
    size_t i;
    size_t j;

    if (tuples == NULL || out_groups == NULL || out_count == NULL) {
        return -1;
    }

    groups = malloc(n * sizeof(Group));
    if (groups == NULL) {
        return -1;
    }

    group_count = 0;

    for (i = 0; i < n; i++) {
        size_t found = group_count;

        for (j = 0; j < group_count; j++) {
            if (groups[j].first == tuples[i].first) {
                found = j;
                break;
            }
        }

        if (found == group_count) {
            groups[group_count].first = tuples[i].first;
            groups[group_count].seconds = malloc(n * sizeof(int));
            if (groups[group_count].seconds == NULL) {
                for (j = 0; j < group_count; j++) {
                    free(groups[j].seconds);
                }
                free(groups);
                return -1;
            }
            groups[group_count].count = 0;
            group_count++;
        }

        groups[found].seconds[groups[found].count] = tuples[i].second;
        groups[found].count++;
    }

    *out_groups = groups;
    *out_count = group_count;
    return 0;
}

static void free_groups(Group *groups, size_t count)
{
    size_t i;

    if (groups == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(groups[i].seconds);
    }
    free(groups);
}

int main(void)
{
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {1, 30},
        {3, 40},
        {2, 50},
        {1, 60}
    };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    Group *groups = NULL;
    size_t group_count = 0;
    size_t i;
    size_t j;

    if (group_by_first(tuples, n, &groups, &group_count) != 0) {
        fprintf(stderr, "Failed to group tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < group_count; i++) {
        printf("(%d, [", groups[i].first);
        for (j = 0; j < groups[i].count; j++) {
            printf("%d", groups[i].seconds[j]);
            if (j + 1 < groups[i].count) {
                printf(", ");
            }
        }
        printf("])\n");
    }

    free_groups(groups, group_count);
    return EXIT_SUCCESS;
}