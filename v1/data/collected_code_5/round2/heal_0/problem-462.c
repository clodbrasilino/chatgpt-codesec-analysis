#include <stdio.h>

void findCombinations(char *data, int start, int end, int index, int r, char *list) {
    if (index == r) {
        for (int i = 0; i < r; i++)
            printf("%c ", data[i]);
        printf("\n");
        return;
    }
 
    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = list[i];
        findCombinations(data, i + 1, end, index + 1, r, list);
    }
}
 
void getCombinations(char *list, int n, int r) {
    char data[r];
    findCombinations(data, 0, n - 1, 0, r, list);
}

int main(void) {
    char list[] = {'a', 'b', 'c', 'd', 'e'};
    int n = sizeof(list)/sizeof(list[0]);
    int r = 3;
    getCombinations(list, n, r);
    return 0;
}