#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t count;
} Sublist;

typedef struct {
    Sublist *groups;
    size_t group_count;
} PackedList;

static void free_packed(PackedList *packed)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (packed == NULL) {
        return;
    }
    if (packed->groups != NULL) {
        for (i = 0; i < packed->group_count; i++) {
            free(packed->groups[i].items);
        }
        free(packed->groups);
    }
    free(packed);
}

static PackedList *pack_duplicates(const int *list, size_t length)
{
    PackedList *packed;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    size_t start;
    /* Possible weaknesses found:
     *  The scope of the variable 'run_len' can be reduced. [variableScope]
     */
    size_t run_len;
    size_t j;
    Sublist *tmp;

    packed = malloc(sizeof(PackedList));
    if (packed == NULL) {
        return NULL;
    }
    packed->groups = NULL;
    packed->group_count = 0;

    if (list == NULL || length == 0) {
        return packed;
    }

    i = 0;
    while (i < length) {
        start = i;
        while (i < length && list[i] == list[start]) {
            i++;
        }
        run_len = i - start;

        tmp = realloc(packed->groups,
                      (packed->group_count + 1) * sizeof(Sublist));
        if (tmp == NULL) {
            free_packed(packed);
            return NULL;
        }
        packed->groups = tmp;

        packed->groups[packed->group_count].items =
            malloc(run_len * sizeof(int));
        if (packed->groups[packed->group_count].items == NULL) {
            free_packed(packed);
            return NULL;
        }
        packed->groups[packed->group_count].count = run_len;

        for (j = 0; j < run_len; j++) {
            packed->groups[packed->group_count].items[j] = list[start + j];
        }
        packed->group_count++;
    }

    return packed;
}

static void print_packed(const PackedList *packed)
{
    size_t i;
    size_t j;

    if (packed == NULL) {
        return;
    }
    printf("[");
    for (i = 0; i < packed->group_count; i++) {
        printf("[");
        for (j = 0; j < packed->groups[i].count; j++) {
            printf("%d", packed->groups[i].items[j]);
            if (j + 1 < packed->groups[i].count) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1 < packed->group_count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int list[] = { 1, 1, 2, 3, 3, 3, 4, 4, 5, 1, 1 };
    size_t length;
    PackedList *packed;

    length = sizeof(list) / sizeof(list[0]);

    packed = pack_duplicates(list, length);
    if (packed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    print_packed(packed);
    free_packed(packed);

    return EXIT_SUCCESS;
}