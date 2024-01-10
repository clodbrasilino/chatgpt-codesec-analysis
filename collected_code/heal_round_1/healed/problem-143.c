#include <stdio.h>

int count_lists(int tuple[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] == -1) {
            count++;
        }
    }
    return count;
}

int main() {
    int tuple[] = {1, 2, 3, -1, -1, 4, 5, -1, 6, 7};
    int num_lists = count_lists(tuple, sizeof(tuple) / sizeof(int));
    printf("%d", num_lists);
    return 0;
}