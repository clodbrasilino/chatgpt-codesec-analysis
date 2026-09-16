#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->first != tb->first) {
        return ta->first - tb->first;
    }
    return ta->second - tb->second;
}

int tuples_equal(const Tuple *a, const Tuple *b) {
    return a->first == b->first && a->second == b->second;
}

TupleList *find_similar_tuples(const TupleList *list1, const TupleList *list2) {
    if (list1 == NULL || list2 == NULL || list1->tuples == NULL || list2->tuples == NULL) {
        return NULL;
    }
    
    if (list1->size == 0 || list2->size == 0) {
        TupleList *result = malloc(sizeof(TupleList));
        if (result == NULL) {
            return NULL;
        }
        result->tuples = NULL;
        result->size = 0;
        return result;
    }
    
    Tuple *sorted1 = malloc(list1->size * sizeof(Tuple));
    Tuple *sorted2 = malloc(list2->size * sizeof(Tuple));
    
    if (sorted1 == NULL || sorted2 == NULL) {
        free(sorted1);
        free(sorted2);
        return NULL;
    }
    
    memcpy(sorted1, list1->tuples, list1->size * sizeof(Tuple));
    memcpy(sorted2, list2->tuples, list2->size * sizeof(Tuple));
    
    qsort(sorted1, list1->size, sizeof(Tuple), compare_tuples);
    qsort(sorted2, list2->size, sizeof(Tuple), compare_tuples);
    
    size_t max_size = list1->size < list2->size ? list1->size : list2->size;
    Tuple *common = malloc(max_size * sizeof(Tuple));
    
    if (common == NULL) {
        free(sorted1);
        free(sorted2);
        return NULL;
    }
    
    size_t i = 0, j = 0, count = 0;
    
    while (i < list1->size && j < list2->size) {
        int cmp = compare_tuples(&sorted1[i], &sorted2[j]);
        if (cmp == 0) {
            if (count == 0 || !tuples_equal(&common[count - 1], &sorted1[i])) {
                common[count] = sorted1[i];
                count++;
            }
            i++;
            j++;
        } else if (cmp < 0) {
            i++;
        } else {
            j++;
        }
    }
    
    free(sorted1);
    free(sorted2);
    
    TupleList *result = malloc(sizeof(TupleList));
    if (result == NULL) {
        free(common);
        return NULL;
    }
    
    result->tuples = common;
    result->size = count;
    
    return result;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL) {
        free(list->tuples);
        free(list);
    }
}

int main(void) {
    Tuple arr1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {3, 4}};
    Tuple arr2[] = {{3, 4}, {5, 6}, {9, 10}, {3, 4}, {11, 12}};
    
    TupleList list1 = {arr1, sizeof(arr1) / sizeof(arr1[0])};
    TupleList list2 = {arr2, sizeof(arr2) / sizeof(arr2[0])};
    
    TupleList *similar = find_similar_tuples(&list1, &list2);
    
    if (similar == NULL) {
        fprintf(stderr, "Error: Failed to find similar tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("Similar tuples: ");
    for (size_t i = 0; i < similar->size; i++) {
        printf("(%d, %d) ", similar->tuples[i].first, similar->tuples[i].second);
    }
    printf("\n");
    
    free_tuple_list(similar);
    
    return EXIT_SUCCESS;
}