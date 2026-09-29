#include <stdio.h>

typedef struct ListOfLists {
    struct ListOfLists *next;
} ListOfLists;

int count_lists_and_square(ListOfLists *lists) {
    int count = 0;

    while (lists != NULL) {
        count++;
        lists = lists->next;
    }

    return count * count;
}

int main(void) {
    ListOfLists outer2 = { NULL };
    ListOfLists outer1 = { &outer2 };

    printf("%d\n", count_lists_and_square(&outer1));

    return 0;
}