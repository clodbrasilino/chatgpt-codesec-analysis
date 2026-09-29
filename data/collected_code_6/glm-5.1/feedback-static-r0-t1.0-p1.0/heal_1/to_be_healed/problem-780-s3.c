#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    int size;
} Tuple;

typedef struct {
    int *items;
    int size;
} TupleList;

int *prefix_sums = NULL;
int **combinations = NULL;
int combinations_size = 0;
int combinations_capacity = 0;

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
void add_combination(int *tuple, int size) {
    if (combinations_size >= combinations_capacity) {
        combinations_capacity = combinations_capacity == 0 ? 4 : combinations_capacity * 2;
        combinations = realloc(combinations, combinations_capacity * sizeof(int *));
        /* Possible weaknesses found:
         *  Assuming that condition 'combinations==NULL' is not redundant
         */
        if (combinations == NULL) {
            free(prefix_sums);
            for (int i = 0; i < combinations_size; i++) {
                /* Possible weaknesses found:
                 *  Null pointer dereference
                 *  Either the condition 'combinations==NULL' is redundant or there is possible null pointer dereference: combinations. [nullPointerRedundantCheck]
                 */
                free(combinations[i]);
            }
            exit(EXIT_FAILURE);
        }
    }
    combinations[combinations_size] = malloc(size * sizeof(int));
    if (combinations[combinations_size] == NULL) {
        free(prefix_sums);
        for (int i = 0; i < combinations_size; i++) {
            free(combinations[i]);
        }
        free(combinations);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        combinations[combinations_size][i] = tuple[i];
    }
    combinations_size++;
}

void find_combinations_util(TupleList *list, int target, int index, int current_sum, int *current_tuple, int tuple_size) {
    if (current_sum == target && tuple_size > 0) {
        add_combination(current_tuple, tuple_size);
    }
    if (current_sum >= target || index >= list->size) {
        return;
    }
    for (int i = index; i < list->size; i++) {
        /* Possible weaknesses found:
         *  request for member 'size' in something not a structure or union
         *  member reference base type 'int' is not a structure or union
         */
        for (int j = 0; j < list->items[i].size; j++) {
            /* Possible weaknesses found:
             *  request for member 'items' in something not a structure or union
             *  member reference base type 'int' is not a structure or union
             */
            int item = list->items[i].items[j];
            if (current_sum + item > target) {
                continue;
            }
            current_tuple[tuple_size] = item;
            find_combinations_util(list, target, i + 1, current_sum + item, current_tuple, tuple_size + 1);
        }
    }
}

int **find_combinations(TupleList *list, int target, int *return_size, int **return_column_sizes) {
    if (list == NULL || list->size == 0) {
        *return_size = 0;
        *return_column_sizes = NULL;
        return NULL;
    }
    if (prefix_sums != NULL) {
        free(prefix_sums);
        prefix_sums = NULL;
    }
    if (combinations != NULL) {
        for (int i = 0; i < combinations_size; i++) {
            free(combinations[i]);
        }
        free(combinations);
        combinations = NULL;
    }
    combinations_size = 0;
    combinations_capacity = 0;

    prefix_sums = malloc(list->size * sizeof(int));
    if (prefix_sums == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < list->size; i++) {
        /* Possible weaknesses found:
         *  request for member 'items' in something not a structure or union
         *  member reference base type 'int' is not a structure or union
         */
        int min_val = list->items[i].items[0];
        /* Possible weaknesses found:
         *  request for member 'size' in something not a structure or union
         *  member reference base type 'int' is not a structure or union
         */
        for (int j = 1; j < list->items[i].size; j++) {
            /* Possible weaknesses found:
             *  request for member 'items' in something not a structure or union
             *  member reference base type 'int' is not a structure or union
             */
            if (list->items[i].items[j] < min_val) {
                /* Possible weaknesses found:
                 *  request for member 'items' in something not a structure or union
                 *  member reference base type 'int' is not a structure or union
                 */
                min_val = list->items[i].items[j];
            }
        }
        prefix_sums[i] = (i == 0) ? min_val : prefix_sums[i - 1] + min_val;
    }

    int *current_tuple = malloc(list->size * sizeof(int));
    if (current_tuple == NULL) {
        free(prefix_sums);
        exit(EXIT_FAILURE);
    }

    find_combinations_util(list, target, 0, 0, current_tuple, 0);

    free(current_tuple);
    free(prefix_sums);
    prefix_sums = NULL;

    *return_size = combinations_size;
    *return_column_sizes = malloc(combinations_size * sizeof(int));
    if (*return_column_sizes == NULL) {
        for (int i = 0; i < combinations_size; i++) {
            free(combinations[i]);
        }
        free(combinations);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < combinations_size; i++) {
        int count = 0;
        for (int j = 0; j < list->size; j++) {
            if (combinations[i][j] != 0 || j == 0) {
                count++;
            }
        }
        (*return_column_sizes)[i] = count;
    }

    return combinations;
}

int main() {
    int a1[] = {1, 2};
    int a2[] = {3, 4};
    int a3[] = {5};
    
    Tuple tuples[] = {
        {a1, 2},
        {a2, 2},
        {a3, 1}
    };
    
    /* Possible weaknesses found:
     *  (near initialization for 'list.items')
     *  initialization of 'int *' from incompatible pointer type 'Tuple *' [-Wincompatible-pointer-types]
     */
    TupleList list = {tuples, 3};
    int target = 8;
    int return_size = 0;
    int *return_column_sizes = NULL;
    
    int **result = find_combinations(&list, target, &return_size, &return_column_sizes);
    
    for (int i = 0; i < return_size; i++) {
        for (int j = 0; j < return_column_sizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }
    
    free(return_column_sizes);
    free(result);
    
    return 0;
}