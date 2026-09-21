#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int len;
} List;

int compare_lists(const void *a, const void *b) {
    const List *la = (const List *)a;
    const List *lb = (const List *)b;
    
    if (la->len != lb->len) {
        return (la->len > lb->len) - (la->len < lb->len);
    }
    
    for (int i = 0; i < la->len; i++) {
        if (la->data[i] != lb->data[i]) {
            return (la->data[i] > lb->data[i]) - (la->data[i] < lb->data[i]);
        }
    }
    
    return 0;
}

void free_lists(List *lists, int count) {
    if (lists == NULL) return;
    for (int i = 0; i < count; i++) {
        free(lists[i].data);
    }
    free(lists);
}

int main(void) {
    int count = 4;
    List *lists = (List *)malloc(count * sizeof(List));
    if (lists == NULL) {
        return 1;
    }
    
    int a0[] = {3, 1, 2};
    lists[0].len = 3;
    lists[0].data = (int *)malloc(lists[0].len * sizeof(int));
    if (lists[0].data == NULL) {
        free(lists);
        return 1;
    }
    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    memcpy_s(lists[0].data, lists[0].len * sizeof(int), a0, sizeof(a0));
    
    int a1[] = {1, 1};
    lists[1].len = 2;
    lists[1].data = (int *)malloc(lists[1].len * sizeof(int));
    if (lists[1].data == NULL) {
        free_lists(lists, 1);
        return 1;
    }
    memcpy_s(lists[1].data, lists[1].len * sizeof(int), a1, sizeof(a1));
    
    int a2[] = {1, 2, 3};
    lists[2].len = 3;
    lists[2].data = (int *)malloc(lists[2].len * sizeof(int));
    if (lists[2].data == NULL) {
        free_lists(lists, 2);
        return 1;
    }
    memcpy_s(lists[2].data, lists[2].len * sizeof(int), a2, sizeof(a2));
    
    int a3[] = {5};
    lists[3].len = 1;
    lists[3].data = (int *)malloc(lists[3].len * sizeof(int));
    if (lists[3].data == NULL) {
        free_lists(lists, 3);
        return 1;
    }
    memcpy_s(lists[3].data, lists[3].len * sizeof(int), a3, sizeof(a3));
    
    /* Possible weaknesses found:
     *  'memcpy' declared here
     */
    qsort(lists, count, sizeof(List), compare_lists);
    
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < lists[i].len; j++) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }
    
    free_lists(lists, count);
    
    return 0;
}