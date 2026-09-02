#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
    int capacity;
} TupleList;

typedef struct {
    Tuple *combinations;
    int count;
} CombinationResult;

void init_tuple_list(TupleList *list) {
    list->tuples = NULL;
    list->count = 0;
    list->capacity = 0;
}

int add_tuple(TupleList *list, int first, int second) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_tuples = (Tuple *)realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (new_tuples == NULL) {
            return -1;
        }
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    list->tuples[list->count].first = first;
    list->tuples[list->count].second = second;
    list->count++;
    return 0;
}

void free_tuple_list(TupleList *list) {
    if (list->tuples != NULL) {
        free(list->tuples);
        list->tuples = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->first != tb->first) {
        return ta->first - tb->first;
    }
    return ta->second - tb->second;
}

int tuple_equal(Tuple a, Tuple b) {
    return a.first == b.first && a.second == b.second;
}

CombinationResult *find_combinations(TupleList *list, int target_sum) {
    if (list == NULL || list->count == 0) {
        return NULL;
    }

    int max_combinations = 1;
    for (int i = 0; i < list->count; i++) {
        max_combinations *= 2;
    }
    if (max_combinations <= 0 || max_combinations > 1000000) {
        return NULL;
    }

    CombinationResult *result = (CombinationResult *)malloc(sizeof(CombinationResult));
    if (result == NULL) {
        return NULL;
    }
    result->combinations = (Tuple *)malloc(max_combinations * sizeof(Tuple));
    if (result->combinations == NULL) {
        free(result);
        return NULL;
    }
    result->count = 0;

    Tuple *temp = (Tuple *)malloc(list->count * sizeof(Tuple));
    if (temp == NULL) {
        free(result->combinations);
        free(result);
        return NULL;
    }

    int total_subsets = 1 << list->count;
    if (total_subsets > max_combinations) {
        free(temp);
        free(result->combinations);
        free(result);
        return NULL;
    }

    for (int mask = 1; mask < total_subsets; mask++) {
        int current_sum = 0;
        int temp_count = 0;
        for (int i = 0; i < list->count; i++) {
            if (mask & (1 << i)) {
                current_sum += list->tuples[i].first;
                current_sum += list->tuples[i].second;
                temp[temp_count] = list->tuples[i];
                temp_count++;
            }
        }
        if (current_sum == target_sum && temp_count > 0) {
            for (int i = 0; i < temp_count; i++) {
                int found = 0;
                for (int j = 0; j < result->count; j++) {
                    if (tuple_equal(result->combinations[j], temp[i])) {
                        found = 1;
                        break;
                    }
                }
                if (!found && result->count < max_combinations) {
                    result->combinations[result->count] = temp[i];
                    result->count++;
                }
            }
        }
    }

    free(temp);

    if (result->count == 0) {
        free(result->combinations);
        free(result);
        return NULL;
    }

    qsort(result->combinations, result->count, sizeof(Tuple), compare_tuples);

    int unique_count = 0;
    if (result->count > 0) {
        unique_count = 1;
        for (int i = 1; i < result->count; i++) {
            if (!tuple_equal(result->combinations[i], result->combinations[unique_count - 1])) {
                result->combinations[unique_count] = result->combinations[i];
                unique_count++;
            }
        }
    }
    result->count = unique_count;

    Tuple *shrunk = (Tuple *)realloc(result->combinations, result->count * sizeof(Tuple));
    if (shrunk != NULL || result->count == 0) {
        result->combinations = shrunk;
    }

    return result;
}

void free_combination_result(CombinationResult *result) {
    if (result != NULL) {
        if (result->combinations != NULL) {
            free(result->combinations);
        }
        free(result);
    }
}

int main(void) {
    TupleList list;
    init_tuple_list(&list);

    add_tuple(&list, 1, 2);
    add_tuple(&list, 2, 3);
    add_tuple(&list, 3, 4);
    add_tuple(&list, 1, 1);
    add_tuple(&list, 5, 5);

    int target = 10;
    CombinationResult *result = find_combinations(&list, target);

    if (result == NULL) {
        printf("No combinations found for sum %d\n", target);
    } else {
        printf("Combinations for sum %d:\n", target);
        for (int i = 0; i < result->count; i++) {
            printf("(%d, %d)\n", result->combinations[i].first, result->combinations[i].second);
        }
        free_combination_result(result);
    }

    free_tuple_list(&list);
    return 0;
}