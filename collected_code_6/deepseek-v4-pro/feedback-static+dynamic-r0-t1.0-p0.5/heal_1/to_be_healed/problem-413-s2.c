#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **elements;
    int count;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

void *extract_nth_element(TupleList *list, int tuple_index, int element_index) {
    if (list == NULL || tuple_index < 0 || tuple_index >= list->count) {
        return NULL;
    }
    
    Tuple *tuple = &list->tuples[tuple_index];
    if (element_index < 0 || element_index >= tuple->count) {
        return NULL;
    }
    
    return tuple->elements[element_index];
}

int main(void) {
    int a = 10, b = 20, c = 30;
    char *str1 = "hello", *str2 = "world";
    double d = 3.14;
    
    void *elements1[] = {&a, &b, &c};
    void *elements2[] = {str1, str2, &d};
    
    Tuple tuples[2];
    tuples[0].elements = elements1;
    tuples[0].count = 3;
    tuples[1].elements = elements2;
    tuples[1].count = 3;
    
    TupleList list;
    list.tuples = tuples;
    list.count = 2;
    
    /* Possible weaknesses found:
     *  Variable 'result1' can be declared as pointer to const [constVariablePointer]
     */
    int *result1 = (int *)extract_nth_element(&list, 0, 1);
    if (result1 != NULL) {
        printf("%d\n", *result1);
    }
    
    char *result2 = (char *)extract_nth_element(&list, 1, 0);
    if (result2 != NULL) {
        printf("%s\n", result2);
    }
    
    /* Possible weaknesses found:
     *  Variable 'result3' can be declared as pointer to const [constVariablePointer]
     */
    double *result3 = (double *)extract_nth_element(&list, 1, 2);
    if (result3 != NULL) {
        printf("%f\n", *result3);
    }
    
    /* Possible weaknesses found:
     *  Variable 'result4' can be declared as pointer to const [constVariablePointer]
     */
    void *result4 = extract_nth_element(&list, 5, 0);
    if (result4 == NULL) {
        printf("Invalid tuple index\n");
    }
    
    /* Possible weaknesses found:
     *  Variable 'result5' can be declared as pointer to const [constVariablePointer]
     */
    void *result5 = extract_nth_element(&list, 0, 10);
    if (result5 == NULL) {
        printf("Invalid element index\n");
    }
    
    return 0;
}