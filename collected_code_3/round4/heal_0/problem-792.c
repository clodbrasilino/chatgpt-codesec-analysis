#include <stdio.h>

typedef struct List {
    int data;
    struct List *next;
} List;

int countLists(List **lists, int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main() {
    int size = 5;
    List *lists[5] = {NULL, NULL, NULL, NULL, NULL};

    List a = {1, NULL};
    List b = {2, NULL};
    List c = {3, NULL};

    lists[0] = &a;
    lists[2] = &b;
    lists[4] = &c;

    printf("Number of lists: %d\n", countLists(lists, size));

    return 0;
}