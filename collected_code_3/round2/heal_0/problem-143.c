#include <stdio.h>

int count_lists(char *tuple) {
    int count = 0;
    for (int i = 0; tuple[i] != '\0'; i++) {
        if (tuple[i] == '[') {
            count++;
        }
    }
    return count;
}

int main() {
    char tuple[] = "(1, [2, 3], 4, [5, 6, 7], 8, [9])";
    printf("Number of lists in the tuple: %d\n", count_lists(tuple));
    return 0;
}