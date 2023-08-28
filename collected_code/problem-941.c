#include <stdio.h>

int count_until_tuple(int* list) {
    int count = 0;

    while (*list) {
        if (*list == -1) {
            break;
        }
        count++;
        list++;
    }
    return count;
}

int main() {
    int list[6] = {1, 2, 3, 4, 5, -1};
    int count = count_until_tuple(list);
    printf("Count: %d\n", count);
    
    return 0;
}