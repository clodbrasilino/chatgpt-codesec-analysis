#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

typedef struct {
    int **combinations;
    int count;
    int capacity;
} CombinationResult;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int min_size = ta->size < tb->size ? ta->size : tb->size;
    for (int i = 0; i < min_size; i++) {
        if (ta->elements[i] != tb->elements[i]) {
            return ta->elements[i] - tb->elements[i];
        }
    }
    return ta->size - tb->size;
}

int tuples_equal(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) return 0;
    for (int i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) return 0;
    }
    return 1;
}

int add_combination(CombinationResult *result, int *combo, int combo_size) {
    if (result->count >= result->capacity) {
        int new_capacity = result->capacity == 0 ? 16 : result->capacity * 2;
        int **new_combinations = (int **)realloc(result->combinations, new_capacity * sizeof(int *));
        if (new_combinations == NULL) {
            return -1;
        }
        result->combinations = new_combinations;
        result->capacity = new_capacity;
    }
    
    int *new_combo = (int *)malloc(combo_size * sizeof(int));
    if (new_combo == NULL) {
        return -1;
    }
    memcpy(new_combo, combo, combo_size * sizeof(int));
    result->combinations[result->count] = new_combo;
    result->count++;
    return 0;
}

void find_combinations_recursive(TupleList *list, int target, int start, 
                                  int *current, int current_size, 
                                  CombinationResult *result, int *used) {
    if (target == 0) {
        add_combination(result, current, current_size);
        return;
    }
    if (target < 0 || start >= list->count) {
        return;
    }
    
    for (int i = start; i < list->count; i++) {
        if (used[i]) continue;
        
        int sum = 0;
        for (int j = 0; j < list->tuples[i].size; j++) {
            sum += list->tuples[i].elements[j];
        }
        
        used[i] = 1;
        current[current_size] = i;
        find_combinations_recursive(list, target - sum, i + 1, current, 
                                     current_size + 1, result, used);
        used[i] = 0;
    }
}

CombinationResult find_combinations(TupleList *list, int target) {
    CombinationResult result;
    result.combinations = NULL;
    result.count = 0;
    result.capacity = 0;
    
    if (list == NULL || list->count <= 0) {
        return result;
    }
    
    int *used = (int *)calloc(list->count, sizeof(int));
    if (used == NULL) {
        return result;
    }
    
    int *current = (int *)malloc(list->count * sizeof(int));
    if (current == NULL) {
        free(used);
        return result;
    }
    
    find_combinations_recursive(list, target, 0, current, 0, &result, used);
    
    free(used);
    free(current);
    return result;
}

void free_combination_result(CombinationResult *result) {
    if (result == NULL) return;
    for (int i = 0; i < result->count; i++) {
        free(result->combinations[i]);
    }
    free(result->combinations);
    result->combinations = NULL;
    result->count = 0;
    result->capacity = 0;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) return;
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

/* Possible weaknesses found:
 *  Parameter 'tuple_sizes' can be declared as const array [constParameter]
 */
int create_tuple_list(TupleList *list, int tuple_data[][3], int tuple_sizes[], int count) {
    list->tuples = (Tuple *)malloc(count * sizeof(Tuple));
    if (list->tuples == NULL) {
        return -1;
    }
    list->count = count;
    
    for (int i = 0; i < count; i++) {
        list->tuples[i].size = tuple_sizes[i];
        list->tuples[i].elements = (int *)malloc(tuple_sizes[i] * sizeof(int));
        if (list->tuples[i].elements == NULL) {
            for (int j = 0; j < i; j++) {
                free(list->tuples[j].elements);
            }
            free(list->tuples);
            list->tuples = NULL;
            list->count = 0;
            return -1;
        }
        for (int j = 0; j < tuple_sizes[i]; j++) {
            list->tuples[i].elements[j] = tuple_data[i][j];
        }
    }
    return 0;
}

int tuple_sum(const Tuple *t) {
    int sum = 0;
    for (int i = 0; i < t->size; i++) {
        sum += t->elements[i];
    }
    return sum;
}

int main(void) {
    int tuple_data[][3] = {{2, 4, 0}, {6, 3, 0}, {2, 7, 0}, {8, 1, 0}, {5, 4, 0}};
    int tuple_sizes[] = {2, 2, 2, 2, 2};
    int count = 5;
    int target = 8;
    
    TupleList list;
    if (create_tuple_list(&list, tuple_data, tuple_sizes, count) != 0) {
        fprintf(stderr, "Failed to create tuple list\n");
        return 1;
    }
    
    printf("Tuples:\n");
    for (int i = 0; i < list.count; i++) {
        printf("  (");
        for (int j = 0; j < list.tuples[i].size; j++) {
            printf("%d", list.tuples[i].elements[j]);
            if (j < list.tuples[i].size - 1) printf(", ");
        }
        printf(") sum=%d\n", tuple_sum(&list.tuples[i]));
    }
    
    printf("\nTarget sum: %d\n", target);
    
    CombinationResult result = find_combinations(&list, target);
    
    printf("\nCombinations found: %d\n", result.count);
    for (int i = 0; i < result.count; i++) {
        printf("  Combination %d: ", i + 1);
        for (int j = 0; j < result.count; j++) {
            int idx = result.combinations[i][j];
            printf("(");
            for (int k = 0; k < list.tuples[idx].size; k++) {
                printf("%d", list.tuples[idx].elements[k]);
                if (k < list.tuples[idx].size - 1) printf(", ");
            }
            printf(")");
            if (j < result.count - 1) printf(" + ");
        }
        printf("\n");
    }
    
    free_combination_result(&result);
    free_tuple_list(&list);
    
    return 0;
}