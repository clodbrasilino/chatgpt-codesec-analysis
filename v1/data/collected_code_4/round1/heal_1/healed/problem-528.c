#include<stdio.h>
#include<stdlib.h>

typedef struct List {
    int len;
    int *list;
} List;

List **findShortestList(List **lists, int len) {
    if (len == 0) {
        return NULL;
    }

    List **shortList = (List**) malloc(len * sizeof(List *));
    int count = 0;
    int shortest = -1;

    for (int i = 0; i < len; i++) {
        if(shortest == -1 || lists[i]->len < shortest){
            shortest = lists[i]->len;
            count = 0;
        }
        if(lists[i]->len == shortest){
            shortList[count] = lists[i];
            count++;
        }
    }

    List **res = (List**) realloc(shortList, count * sizeof(List *));
    return res;
}

List *makeList(int len, int *arr) {
    List *newList = (List*) malloc(sizeof(List));
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

    free(list1);
    free(list2);
    free(list3);
    free(result);
    
    return 0;
}