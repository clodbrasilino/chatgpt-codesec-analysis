#include <stdlib.h>
#include <stdio.h>

struct my_double_list {
    int count;
    struct my_double_list* pNext;
};

struct my_double_list* createList(int arr[], int size);
void createPairCountMap(struct my_double_list* list, int pairCountMap[]);
int countSamePairs(struct my_double_list* list1, struct my_double_list* list2);

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6}, arr2[] = {4, 5, 6, 7, 8, 9};
    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int size2 = sizeof(arr2)/sizeof(arr2[0]);

    struct my_double_list* list1 = createList(arr1, size1);
    struct my_double_list* list2 = createList(arr2, size2);

    int result = countSamePairs(list1, list2);
    printf("Number of same pairs: %d\n", result);

    free(list1);
    free(list2);

    return 0;
}

struct my_double_list* createList(int arr[], int size) {
    if(size <= 0) return NULL;

    struct my_double_list* list = malloc(size * sizeof(struct my_double_list));
     
    if(list == NULL) return NULL;

    for(int i = 0; i < size; i++) {
        list[i].count = arr[i];
        list[i].pNext = (i < size - 1) ? (&list[i+1]) : NULL;
    }

    return list;
}

void createPairCountMap(struct my_double_list* list, int pairCountMap[]) {
    if(!list || !pairCountMap) return;

    while(list->pNext != NULL) {
        pairCountMap[list->count]++;
        pairCountMap[list->pNext->count]++;
        list = list->pNext->pNext;
    }
}

int countSamePairs(struct my_double_list* list1, struct my_double_list* list2) {
    if(!list1 || !list2) return 0;

    int pairCountMap1[100] = {0}, pairCountMap2[100] = {0};
    createPairCountMap(list1, pairCountMap1);
    createPairCountMap(list2, pairCountMap2);

    int count = 0;

    for(int i = 0; i < 100; i++) {
       if(pairCountMap1[i] && pairCountMap2[i]) {
          count++;
       }
    }

    return count;
}