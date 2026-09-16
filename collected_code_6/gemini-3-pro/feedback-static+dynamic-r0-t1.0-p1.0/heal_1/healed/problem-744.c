#include <stdio.h>
#include <stdbool.h>

typedef struct {
    void *item1;
    void *item2;
    void *item3;
} Tuple;

bool check_none(const Tuple *tuple) {
    if (tuple == NULL) {
        return true;
    }
    
    if (tuple->item1 == NULL || tuple->item2 == NULL || tuple->item3 == NULL) {
        return true;
    }
    
    return false;
}

int main(void) {
    int a = 10;
    int b = 20;
    
    Tuple t1 = {&a, &b, NULL};
    Tuple t2 = {&a, &b, &a};
    Tuple *t3 = NULL;
    
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
    
    if (check_none(t3)) {
        printf("Tuple pointer is NULL.\n");
    }
    
    return 0;
}