#include <stddef.h>
#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'lengths' can be declared as pointer to const [constParameterPointer]
 */
int *find_max_sublist(int **sublists, size_t count, size_t *lengths, size_t *max_length) {
    if (sublists == NULL || lengths == NULL || max_length == NULL || count == 0) {
        if (max_length != NULL) {
            *max_length = 0;
        }
        return NULL;
    }

    size_t max_index = 0;
    size_t max_len = lengths[0];

    for (size_t i = 1; i < count; ++i) {
        if (lengths[i] > max_len) {
            max_len = lengths[i];
            max_index = i;
        }
    }

    *max_length = max_len;
    return sublists[max_index];
}

int main(void) {
    int sublist0[] = {1, 2, 3};
    int sublist1[] = {4, 5};
    int sublist2[] = {6, 7, 8, 9};

    int *sublists[] = {sublist0, sublist1, sublist2};
    size_t lengths[] = {3, 2, 4};
    size_t count = sizeof(sublists) / sizeof(sublists[0]);

    size_t max_length = 0;
    /* Possible weaknesses found:
     *  Variable 'max_sublist' can be declared as pointer to const [constVariablePointer]
     */
    int *max_sublist = find_max_sublist(sublists, count, lengths, &max_length);

    if (max_sublist != NULL) {
        for (size_t i = 0; i < max_length; ++i) {
            printf("%d", max_sublist[i]);
            if (i + 1 < max_length) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}