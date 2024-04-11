#include <stdio.h>
#include <stdbool.h>

#define SIZE 5

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
    Tuple list1[SIZE] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    Tuple list2[SIZE] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    Tuple list3[SIZE] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 11}};

    if (areIdentical(list1, list2, SIZE)) {
        printf("List1 and List2 are identical\n");
    } else {
        printf("List1 and List2 are not identical\n");
    }

    if (areIdentical(list1, list3, SIZE)) {
        printf("List1 and List3 are identical\n");
    } else {
        printf("List1 and List3 are not identical\n");
    }

    return 0;
}