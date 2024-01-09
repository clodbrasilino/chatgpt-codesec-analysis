#include <stdio.h>

int count_lists(int tuple[]) {
    int count = 0;
    for (int i = 0; i < sizeof(tuple); i++) {
        if (typeof(tuple[i]) == list) {
            count++;
        }
    }
    return count;
}

int main() {
    int tuple[] = {1, 2, 3, [4, 5], [6, 7]};
    int num_lists = count_lists(tuple);
    printf("%d", num_lists);
    return 0;
}