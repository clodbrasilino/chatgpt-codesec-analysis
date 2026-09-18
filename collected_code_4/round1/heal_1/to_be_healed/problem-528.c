#include<stdio.h>
#include<stdlib.h>

typedef struct List {
    int len;
    int *list;
} List;

int shortest = -1;

List **findShortestList(List **lists, int len) {
    if (len == 0) {
        return NULL;
    }

    List **shortList = malloc(len * sizeof(*shortList));
    int count = 0;

    for (int i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'sharedt' undeclared (first use in this function)
         */
        if(sharedt == -1 || lists[i]->len < sharedt){
            sharedt = lists[i]->len;
            count = 0;
        }
        if(lists[i]->len == sharedt){
            shortList[count] = lists[i];
            count++;
        }
    }

    List **res = realloc(shortList, count * sizeof(*shortList));
    return res;
}

List *makeList(int len, int *arr) {
    List *newList = malloc(sizeof(List));
    newList->len = len;
    newList->list = arr;
    return newList;
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {1, 2};
    int arr3[] = {1, 2, 3, 4, 5};
    
    List *list1 = makeList(3, arr1);
    List *list2 = makeList(2, arr2);
    List *list3 = makeList(5, arr3);

    List *lists[3] = {list1, list2, list3};

    List **result = findShortestList(lists, 3);

    return 0;
}