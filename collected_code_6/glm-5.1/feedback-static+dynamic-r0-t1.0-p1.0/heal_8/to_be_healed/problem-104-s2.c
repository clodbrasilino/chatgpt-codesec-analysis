#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    size_t count;
} StringList;

typedef struct {
    StringList *sublists;
    size_t count;
} ListOfLists;

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void free_list_of_lists(ListOfLists *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (list->sublists[i].strings != NULL) {
            for (size_t j = 0; j < list->sublists[i].count; j++) {
                free(list->sublists[i].strings[j]);
            }
            free(list->sublists[i].strings);
        }
    }
    free(list->sublists);
    list->sublists = NULL;
    list->count = 0;
}

int sort_sublists(ListOfLists *list) {
    if (list == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     *  expanded from macro '__darwin_obsz0'
     */
    for (size_t i = 0; i < list->count; i++) {
        if (list->sublists[i].strings != NULL && list->sublists[i].count > 0) {
            qsort(list->sublists[i].strings, list->sublists[i].count, sizeof(char *), compare_strings);
        }
    }
    return 0;
}

ListOfLists create_list_of_lists(size_t sublist_count, const size_t *sublist_sizes) {
    ListOfLists list;
    list.count = sublist_count;
    list.sublists = malloc(list.count * sizeof(StringList));
    if (list.sublists == NULL) {
        list.count = 0;
        return list;
    }
    for (size_t i = 0; i < list.count; i++) {
        list.sublists[i].count = sublist_sizes[i];
        list.sublists[i].strings = malloc(list.sublists[i].count * sizeof(char *));
        if (list.sublists[i].strings == NULL) {
            list.sublists[i].count = 0;
            for (size_t k = 0; k < i; k++) {
                if (list.sublists[k].strings != NULL) {
                    for (size_t j = 0; j < list.sublists[k].count; j++) {
                        /* Possible weaknesses found:
                         *  invalid type argument of '->' (have 'ListOfLists')
                         *  member reference type 'ListOfLists' is not a pointer; did you mean to use '.'?
                         */
                        free(list->sublists[k].strings[j]);
                    }
                    free(list.sublists[k].strings);
                }
            }
            free(list.sublists);
            list.sublists = NULL;
            list.count = 0;
            return list;
        }
        for (size_t j = 0; j < list.sublists[i].count; j++) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char buffer[256];
            int written = snprintf(buffer, sizeof(buffer), "item_%zu_%zu", i, j);
            size_t len;
            if (written < 0 || (size_t)written >= sizeof(buffer)) {
                len = sizeof(buffer) - 1;
            } else {
                len = (size_t)written;
            }
            list.sublists[i].strings[j] = malloc(len + 1);
            if (list.sublists[i].strings[j] == NULL) {
                for (size_t l = 0; l < j; l++) {
                    /* Possible weaknesses found:
                     *  invalid type argument of '->' (have 'ListOfLists')
                     *  member reference type 'ListOfLists' is not a pointer; did you mean to use '.'?
                     */
                    free(list->sublists[i].strings[l]);
                }
                /* Possible weaknesses found:
                 *  invalid type argument of '->' (have 'ListOfLists')
                 *  member reference type 'ListOfLists' is not a pointer; did you mean to use '.'?
                 */
                free(list->sublists[i].strings);
                list.sublists[i].strings = NULL;
                list.sublists[i].count = 0;
                for (size_t k = 0; k < i; k++) {
                    if (list.sublists[k].strings != NULL) {
                        for (size_t m = 0; m < list.sublists[k].count; m++) {
                            /* Possible weaknesses found:
                             *  invalid type argument of '->' (have 'ListOfLists')
                             *  member reference type 'ListOfLists' is not a pointer; did you mean to use '.'?
                             */
                            free(list->sublists[k].strings[m]);
                        }
                        /* Possible weaknesses found:
                         *  invalid type argument of '->' (have 'ListOfLists')
                         *  member reference type 'ListOfLists' is not a pointer; did you mean to use '.'?
                         */
                        free(list->sublists[k].strings);
                    }
                }
                free(list.sublists);
                list.sublists = NULL;
                list.count = 0;
                return list;
            }
            if (len + 1 <= sizeof(buffer)) {
                /* Possible weaknesses found:
                 *  invalid type argument of '->' (have 'ListOfLists')
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 *  member reference type 'ListOfLists' is not a pointer; did you mean to use '.'?
                 */
                memcpy(list->sublists[i].strings[j], buffer, len + 1);
            }
        }
    }
    return list;
}

void print_list_of_lists(const ListOfLists *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        printf("[");
        for (size_t j = 0; j < list->sublists[i].count; j++) {
            printf("%s", list->sublists[i].strings[j]);
            if (j < list->sublists[i].count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
 /* Possible weaknesses found:
  *  expanded from macro '__memcpy_chk_func'
  */

int main(void) {
    size_t sublist_sizes[] = {3, 2, 4};
    size_t num_sublists = sizeof(sublist_sizes) / sizeof(sublist_sizes[0]);

    ListOfLists list = create_list_of_lists(num_sublists, sublist_sizes);
    if (list.sublists == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Before sorting:\n");
    print_list_of_lists(&list);

    if (sort_sublists(&list) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_list_of_lists(&list);
        return EXIT_FAILURE;
    }

    printf("\nAfter sorting:\n");
    print_list_of_lists(&list);

    free_list_of_lists(&list);

    return EXIT_SUCCESS;
}