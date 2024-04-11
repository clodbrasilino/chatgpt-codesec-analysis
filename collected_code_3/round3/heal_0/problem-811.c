#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

bool areIdentical(Tuple list1[], Tuple list2[], int n) {
    for (int i = 0; i < n; i++) {
        if (list1[i].x != list2[i].x || list1[i].y != list2[i].y) {
            return false;
        }
    }
    return true;
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple list2[] = {{1, 2}, {3, 4}, {5, 6}};
    int n = sizeof(list1) / sizeof(list1[0]);

    if (areIdentical(list1, list2, n)) {
        printf("Lists are identical\n");
    } else {
        printf("Lists are not identical\n");
    }

    return 0;
}