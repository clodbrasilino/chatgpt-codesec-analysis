#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t length;
} List;

int compareLengths(const void *a, const void *b) {
    const List *listA = a;
    const List *listB = b;
    return (listB->length - listA->length);
}

List* findLongestLists(List *lists, size_t num_lists, size_t *max_length, size_t *num_longest) {
    qsort(lists, num_lists, sizeof(List), compareLengths);
    *max_length = lists[0].length;
    for (*num_longest = 1; *num_longest < num_lists && lists[*num_longest].length == *max_length; ++*num_longest);
    
    return lists;
}

List createList(int *arr, size_t len) {
    List l;
    l.data = arr;
    l.length = len;
    return l;
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7, 8};
    int arr3[] = {9, 10};
    int arr4[] = {11, 12, 13, 14, 15};

    List lists[] = {
        createList(arr1, 3),
        createList(arr2, 5),
        createList(arr3, 2),
        createList(arr4, 5)
    };

    size_t max_length, num_longest;
    List *result = findLongestLists(lists, 4, &max_length, &num_longest);

    for (size_t i = 0; i < num_longest; ++i) {
        printf("List with length %zu: ", result[i].length);
        for (size_t j = 0; j < result[i].length; ++j) {
            printf("%d ", result[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}