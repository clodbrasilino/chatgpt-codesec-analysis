#include <stdio.h>
#include <stdbool.h>

typedef struct ListElmt_ {
    void *data;
    struct ListElmt_ *next;
} ListElmt;

typedef struct List_ {
    int size;
    ListElmt *head;
    ListElmt *tail;
} List;

typedef struct Tuple_ {
    int size;
    void **elements;
} Tuple;

int count_until_tuple(List *list) {
    int count = 0;
    ListElmt *element;
    
    if (list == NULL || list->head == NULL) {
        return 0;
    }
    
    for (element = list->head; element != NULL; element = element->next) {
        if (element->data == NULL) {
            return count;
        }
        
        /* Possible weaknesses found:
         *  Variable 'tuple_check' can be declared as pointer to const [constVariablePointer]
         */
        Tuple *tuple_check = (Tuple *)element->data;
        /* Possible weaknesses found:
         *  Condition 'tuple_check!=NULL' is always true [knownConditionTrueFalse]
         */
        if (tuple_check != NULL) {
            return count;
        }
        
        count++;
    }
    
    return count;
}

int main(void) {
    List list;
    ListElmt elmt1, elmt2, elmt3;
    int int_data1 = 10;
    int int_data2 = 20;
    Tuple tuple_data;
    
    list.size = 0;
    list.head = &elmt1;
    list.tail = &elmt3;
    
    elmt1.data = &int_data1;
    elmt1.next = &elmt2;
    list.size++;
    
    elmt2.data = &int_data2;
    elmt2.next = &elmt3;
    list.size++;
    
    elmt3.data = &tuple_data;
    elmt3.next = NULL;
    list.size++;
    
    tuple_data.size = 2;
    tuple_data.elements = NULL;
    
    int result = count_until_tuple(&list);
    printf("%d\n", result);
    
    return 0;
}