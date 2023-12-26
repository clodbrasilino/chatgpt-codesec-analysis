#include <stdio.h>

void sortList(char *list, int size) {
    int i, j;
    char temp;

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (list[i] > list[j]) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

int main() {
    char list[] = {'z', 'a', 'b', 'c'};
    int size = sizeof(list) / sizeof(list[0]);

    sortList(list, size);

    for (int i = 0; i < size; i++) {
        printf("%c ", list[i]);
    }

    return 0;
}