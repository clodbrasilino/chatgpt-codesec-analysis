#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

void tuple_init(Tuple *t, size_t size) {
    if (t == NULL) {
        return;
    }
    t->size = size;
    if (size > 0) {
        t->data = malloc(size * sizeof(int));
        if (t->data == NULL) {
            t->size = 0;
        }
    } else {
        t->data = NULL;
    }
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

size_t tuple_union(const Tuple *t1, const Tuple *t2, Tuple *result) {
    size_t i = 0, j = 0, k = 0;
    
    if (t1 == NULL || t2 == NULL || result == NULL) {
        return 0;
    }
    
    size_t max_size = t1->size + t2->size;
    if (max_size == 0) {
        result->data = NULL;
        result->size = 0;
        return 0;
    }
    
    int *temp = malloc(max_size * sizeof(int));
    if (temp == NULL) {
        return 0;
    }
    
    while (i < t1->size && j < t2->size) {
        if (t1->data[i] < t2->data[j]) {
            temp[k++] = t1->data[i++];
        } else if (t1->data[i] > t2->data[j]) {
            temp[k++] = t2->data[j++];
        } else {
            temp[k++] = t1->data[i];
            i++;
            j++;
        }
    }
    
    while (i < t1->size) {
        temp[k++] = t1->data[i++];
    }
    
    while (j < t2->size) {
        temp[k++] = t2->data[j++];
    }
    
    result->data = realloc(temp, k * sizeof(int));
    if (result->data == NULL && k > 0) {
        free(temp);
        return 0;
    }
    result->size = k;
    
    return k;
}

int main(void) {
    Tuple t1, t2, result;
    /* Possible weaknesses found:
     *  The scope of the variable 'arr1' can be reduced. [variableScope]
     */
    int arr1[] = {1, 3, 5, 7};
    /* Possible weaknesses found:
     *  The scope of the variable 'arr2' can be reduced. [variableScope]
     */
    int arr2[] = {2, 3, 4, 5, 6};
    
    tuple_init(&t1, 4);
    tuple_init(&t2, 5);
    
    /* Possible weaknesses found:
     *  Assuming condition 't2.data==NULL' is false
     *  Assuming condition 't1.data==NULL' is false
     */
    if (t1.data == NULL || t2.data == NULL) {
        tuple_free(&t1);
        tuple_free(&t2);
        return 1;
    }
    
    /* Possible weaknesses found:
     *  Condition 't1.data!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 't1.data!=NULL' is always true
     */
    if (t1.size >= 4 && t1.data != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t1.data, arr1, 4 * sizeof(int));
    }
    /* Possible weaknesses found:
     *  Condition 't2.data!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 't2.data!=NULL' is always true
     */
    if (t2.size >= 5 && t2.data != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t2.data, arr2, 5 * sizeof(int));
    }
    
    size_t union_size = tuple_union(&t1, &t2, &result);
    
    if (union_size > 0) {
        printf("Union: ");
        for (size_t i = 0; i < union_size; i++) {
            printf("%d ", result.data[i]);
        }
        printf("\n");
        tuple_free(&result);
    }
    
    tuple_free(&t1);
    tuple_free(&t2);
    
    return 0;
}