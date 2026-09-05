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
    
    /* Possible weaknesses found:
     *  Assuming that condition 'la->len!=lb->len' is not redundant
     */
    if (la->len != lb->len) {
        return (la->len > lb->len) - (la->len < lb->len);
    }
    
    /* Possible weaknesses found:
     *  Condition 'la->len<lb->len' is always false
     *  Condition 'la->len<lb->len' is always false [knownConditionTrueFalse]
     */
    int min_len = la->len < lb->len ? la->len : lb->len;
    for (int i = 0; i < min_len; i++) {
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
    lists[0].data = (int *)malloc(3 * sizeof(int));
    if (lists[0].data == NULL) {
        free(lists);
        return 1;
    }
    memcpy(lists[0].data, a0, 3 * sizeof(int));
    lists[0].len = 3;
    
    int a1[] = {1, 1};
    lists[1].data = (int *)malloc(2 * sizeof(int));
    if (lists[1].data == NULL) {
        free_lists(lists, 1);
        return 1;
    }
    memcpy(lists[1].data, a1, 2 * sizeof(int));
    lists[1].len = 2;
    
    int a2[] = {1, 2, 3};
    lists[2].data = (int *)malloc(3 * sizeof(int));
    if (lists[2].data == NULL) {
        free_lists(lists, 2);
        return 1;
    }
    memcpy(lists[2].data, a2, 3 * sizeof(int));
    lists[2].len = 3;
    
    int a3[] = {5};
    lists[3].data = (int *)malloc(1 * sizeof(int));
    if (lists[3].data == NULL) {
        free_lists(lists, 3);
        return 1;
    }
    memcpy(lists[3].data, a3, 1 * sizeof(int));
    lists[3].len = 1;
    
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