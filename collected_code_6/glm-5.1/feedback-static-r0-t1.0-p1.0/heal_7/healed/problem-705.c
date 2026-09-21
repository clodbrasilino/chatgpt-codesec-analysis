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

List *create_list(List *lists, int index, const int *src, int src_len) {
    lists[index].len = src_len;
    lists[index].data = (int *)malloc(lists[index].len * sizeof(int));
    if (lists[index].data == NULL) {
        free_lists(lists, index);
        return NULL;
    }
    memcpy(lists[index].data, src, lists[index].len * sizeof(int));
    return lists;
}

int main(void) {
    int count = 4;
    List *lists = (List *)malloc(count * sizeof(List));
    if (lists == NULL) {
        return 1;
    }
    
    int a0[] = {3, 1, 2};
    if (create_list(lists, 0, a0, sizeof(a0) / sizeof(a0[0])) == NULL) return 1;
    
    int a1[] = {1, 1};
    if (create_list(lists, 1, a1, sizeof(a1) / sizeof(a1[0])) == NULL) return 1;
    
    int a2[] = {1, 2, 3};
    if (create_list(lists, 2, a2, sizeof(a2) / sizeof(a2[0])) == NULL) return 1;
    
    int a3[] = {5};
    if (create_list(lists, 3, a3, sizeof(a3) / sizeof(a3[0])) == NULL) return 1;
    
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