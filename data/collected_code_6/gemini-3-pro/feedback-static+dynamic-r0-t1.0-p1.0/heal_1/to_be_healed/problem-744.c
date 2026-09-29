#include <stdio.h>
#include <stdbool.h>

typedef struct {
    void *item1;
    void *item2;
    void *item3;
} Tuple;

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
bool check_none(Tuple *tuple) {
    if (tuple == NULL) {
        return true;
    }
    
    if (tuple->item1 == NULL || tuple->item2 == NULL || tuple->item3 == NULL) {
        return true;
    }
    
    return false;
}

int main() {
    int a = 10;
    int b = 20;
    
    Tuple t1 = {&a, &b, NULL};
    Tuple t2 = {&a, &b, &a};
    
    if (check_none(&t1)) {
        printf("Tuple 1 has None (NULL) values.\n");
    } else {
        printf("Tuple 1 does not have None (NULL) values.\n");
    }
    
    if (check_none(&t2)) {
        printf("Tuple 2 has None (NULL) values.\n");
    } else {
        printf("Tuple 2 does not have None (NULL) values.\n");
    }
    
    /* Possible weaknesses found:
     *  Condition 'check_none(NULL)' is always true [knownConditionTrueFalse]
     *  Condition 'check_none(NULL)' is always true
     *  Calling function 'check_none' returns 1
     */
    if (check_none(NULL)) {
        printf("Tuple pointer is NULL.\n");
    }
    
    return 0;
}