#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int* data;
    int size;
} List;

int countAndSquareLists(List* lists, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (lists[i].data != NULL && lists[i].size > 0) {
            count++;
        }
    }
    return count * count;
}

int main() {
    List lists[3] = {
        { (int[]){1, 2, 3}, 3 },
        { (int[]){4, 5}, 2 },
        { NULL, 0 }
    };

    int result = countAndSquareLists(lists, 3);
    printf("%d\n", result);

    return 0;
}