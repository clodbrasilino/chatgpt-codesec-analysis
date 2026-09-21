#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    for (size_t i = 0; i < list->count; i++) {
        if (list->sublists[i].strings != NULL && list->sublists[i].count > 0) {
            qsort(list->sublists[i].strings, list->sublists[i].count, sizeof(char *), compare_strings);
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  expanded from macro 'NULL'
 */
void cleanup_partial_sublists(StringList *sublists, size_t allocated_count, size_t partial_index, size_t partial_string_count) {
    for (size_t l = 0; l < partial_string_count; l++) {
        free(sublists[partial_index].strings[l]);
    }
    free(sublists[partial_index].strings);
    sublists[partial_index].strings = NULL;
    sublists[partial_index].count = 0;
    for (size_t k = 0; k < allocated_count; k++) {
        if (sublists[k].strings != NULL) {
            for (size_t m = 0; m < sublists[k].count; m++) {
                free(sublists[k].strings[m]);
            }
            free(sublists[k].strings);
        }
    }
    /* Possible weaknesses found:
     *  expanded from macro '__DARWIN_NULL'
     */
    free(sublists);
}

ListOfLists create_list_of_lists(size_t sublist_count, const size_t *sublist_sizes) {
    /* Possible weaknesses found:
     *  initialization of 'long unsigned int' from 'void *' makes integer from pointer without a cast [-Wint-conversion]
     *  (near initialization for 'list.count')
     *  incompatible pointer to integer conversion initializing 'size_t' (aka 'unsigned long') with an expression of type 'void *' [-Wint-conversion]
     */
    ListOfLists list = {0, NULL};
    
    if (sublist_count > 0 && sublist_sizes == NULL) {
        return list;
    }

    if (sublist_count > 0 && sublist_count > SIZE_MAX / sizeof(StringList)) {
        return list;
    }

    list.sublists = (StringList *)malloc(sublist_count * sizeof(StringList));
    if (list.sublists == NULL) {
        return list;
    }
    list.count = sublist_count;

    for (size_t i = 0; i < list.count; i++) {
        list.sublists[i].count = 0;
        list.sublists[i].strings = NULL;
        
        if (sublist_sizes[i] > 0) {
            if (sublist_sizes[i] > SIZE_MAX / sizeof(char *)) {
                cleanup_partial_sublists(list.sublists, i, i, 0);
                list.sublists = NULL;
                list.count = 0;
                return list;
            }
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            list.sublists[i].strings = (char **)malloc(sublist_sizes[i] * sizeof(char *));
            if (list.sublists[i].strings == NULL) {
                cleanup_partial_sublists(list.sublists, i, i, 0);
                list.sublists = NULL;
                list.count = 0;
                return list;
            }
            list.sublists[i].count = sublist_sizes[i];
        }

        for (size_t j = 0; j < list.sublists[i].count; j++) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char buffer[256];
            int written = snprintf(buffer, sizeof(buffer), "item_%zu_%zu", i, j);
            if (written < 0 || (size_t)written >= sizeof(buffer)) {
                cleanup_partial_sublists(list.sublists, i, i, j);
                list.sublists = NULL;
                list.count = 0;
                return list;
            }

            size_t len = (size_t)written;
            if (len > SIZE_MAX - 1) {
                cleanup_partial_sublists(list.sublists, i, i, j);
                list.sublists = NULL;
                list.count = 0;
                return list;
            }
            list.sublists[i].strings[j] = (char *)malloc(len + 1);
            if (list.sublists[i].strings[j] == NULL) {
                cleanup_partial_sublists(list.sublists, i, i, j);
                list.sublists = NULL;
                list.count = 0;
                return list;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(list.sublists[i].strings[j], buffer, len + 1);
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