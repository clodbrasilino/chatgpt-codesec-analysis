#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

typedef struct {
    char **items;
    size_t count;
} StringList;

typedef struct {
    StringList *lists;
    size_t count;
} ListOfLists;

static int compare_strings(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    
    if (*sa == NULL && *sb == NULL) {
        return 0;
    }
    if (*sa == NULL) {
        return -1;
    }
    if (*sb == NULL) {
        return 1;
    }
    
    return strcmp(*sa, *sb);
}

int sort_sublists(ListOfLists *lol)
{
    size_t i;
    if (lol == NULL) {
        return -1;
    }
    if (lol->lists == NULL && lol->count > 0) {
        return -1;
    }
    for (i = 0; i < lol->count; i++) {
        if (lol->lists[i].items != NULL && lol->lists[i].count > 1) {
            if (lol->lists[i].count > SIZE_MAX / sizeof(char *)) {
                return -1;
            }
            qsort(lol->lists[i].items, lol->lists[i].count,
                  sizeof(char *), compare_strings);
        }
    }
    return 0;
}

static char *duplicate_string(const char *s, size_t max_len)
{
    size_t len;
    char *copy;
    
    if (s == NULL) {
        return NULL;
    }
    if (max_len == 0 || max_len > SIZE_MAX - 1) {
        return NULL;
    }
    
    len = strnlen(s, max_len);
    if (len == max_len) {
        return NULL;
    }
    if (len == SIZE_MAX || len >= max_len) {
        return NULL;
    }
    
    if (len + 1 < len) {
        return NULL;
    }
    
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'len>0' is not redundant
     */
    if (len > 0) {
        /* Possible weaknesses found:
         *  Condition 'len+1>0' is always true
         *  Condition 'len+1>0' is always true [knownConditionTrueFalse]
         *  Same expression on both sides of '<='. [duplicateExpression]
         */
        if (len + 1 > 0 && len + 1 <= len + 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(copy, s, len);
        }
    }
    copy[len] = '\0';
    return copy;
}

int init_string_list(StringList *list, const char **strings, size_t count)
{
    size_t i;
    if (list == NULL) {
        return -1;
    }
    list->items = NULL;
    list->count = 0;
    if (count == 0) {
        return 0;
    }
    if (strings == NULL || count > SIZE_MAX / sizeof(char *)) {
        return -1;
    }
    list->items = calloc(count, sizeof(char *));
    if (list->items == NULL) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(list->items[j]);
            }
            free(list->items);
            list->items = NULL;
            return -1;
        }
        list->items[i] = duplicate_string(strings[i], 4096);
        if (list->items[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(list->items[j]);
            }
            free(list->items);
            list->items = NULL;
            return -1;
        }
    }
    list->count = count;
    return 0;
}

void free_string_list(StringList *list)
{
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->items[i]);
        }
        free(list->items);
    }
    list->items = NULL;
    list->count = 0;
}

void free_list_of_lists(ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }
    if (lol->lists != NULL) {
        for (size_t i = 0; i < lol->count; i++) {
            free_string_list(&lol->lists[i]);
        }
        free(lol->lists);
    }
    lol->lists = NULL;
    lol->count = 0;
}

void print_list_of_lists(const ListOfLists *lol)
{
    size_t i, j;
    if (lol == NULL) {
        return;
    }
    if (lol->lists == NULL && lol->count > 0) {
        return;
    }
    for (i = 0; i < lol->count; i++) {
        printf("[");
        if (lol->lists[i].items != NULL) {
            for (j = 0; j < lol->lists[i].count; j++) {
                if (lol->lists[i].items[j] != NULL) {
                    printf("\"%s\"", lol->lists[i].items[j]);
                } else {
                    printf("null");
                }
                if (j + 1 < lol->lists[i].count) {
                    printf(", ");
                }
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    const char *data0[] = {"banana", "apple", "cherry"};
    const char *data1[] = {"dog", "cat"};
    const char *data2[] = {"zebra", "lion", "tiger", "bear"};
    ListOfLists lol;

    lol.lists = calloc(3, sizeof(StringList));
    if (lol.lists == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }
    lol.count = 3;

    if (init_string_list(&lol.lists[0], data0, 3) != 0) {
        fprintf(stderr, "Initialization failed\n");
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    if (init_string_list(&lol.lists[1], data1, 2) != 0) {
        fprintf(stderr, "Initialization failed\n");
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    if (init_string_list(&lol.lists[2], data2, 4) != 0) {
        fprintf(stderr, "Initialization failed\n");
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    printf("Before sorting:\n");
    print_list_of_lists(&lol);

    if (sort_sublists(&lol) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    printf("After sorting:\n");
    print_list_of_lists(&lol);

    free_list_of_lists(&lol);
    return EXIT_SUCCESS;
}