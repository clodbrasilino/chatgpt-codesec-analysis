#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    int size;
} List;

void printSublist(int *sublist, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", sublist[i]);
    }
    printf("\n");
}

void generateSublistsHelper(int *arr, int n, int *sublist, int pos, int depth) {
    if (depth == n) return;
    printSublist(sublist, pos);
    for (int i = depth; i < n; i++) {
        sublist[pos] = arr[i];
        generateSublistsHelper(arr, n, sublist, pos + 1, i + 1);
    }
}

void generateSublists(List *list) {
    int *sublist = (int*)malloc(list->size * sizeof(int));
    if (sublist == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    generateSublistsHelper(list->data, list->size, sublist, 0, 0);
    free(sublist);
}

int main() {
    int arr[] = {1, 2, 3};
    List list = {arr, 3};

    generateSublists(&list);

    return 0;
}