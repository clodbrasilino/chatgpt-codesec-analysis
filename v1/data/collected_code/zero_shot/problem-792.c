#include <stdio.h>

int countLists(int numOfLists, int list[]) {
    int count = 0;

    for (int i = 0; i < numOfLists; i++) {
        if (list[i] == -1) {
            count++;
        }
    }

    return count;
}

int main() {
    int num1[] = {-1, 2, 3, -1, 5, -1};
    int num2[] = {-1, -1, -1};
    int num3[] = {1, 2, 3};

    int numOfLists = 6;
    int *lists[] = {num1, num2, num3};

    int result = countLists(numOfLists, lists);
    printf("Number of lists: %d\n", result);

    return 0;
}