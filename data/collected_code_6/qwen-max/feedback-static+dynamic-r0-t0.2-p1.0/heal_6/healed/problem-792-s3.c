#include <stdio.h>
#include <stdlib.h>

int count_lists(int num_lists) {
    if (num_lists < 0) {
        return -1;
    }
    return num_lists;
}

int main() {
    int num_lists = 5;
    int result = count_lists(num_lists);

    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("Number of lists: %d\n", result);
    }

    return 0;
}