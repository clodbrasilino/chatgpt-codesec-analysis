#include <stdio.h>

typedef struct List {
    struct List *next;
} List;

int count_lists(const List *list) {
    int count = 0;
    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}

int main(void) {
    List l1 = { NULL };
    List l2 = { NULL };
    List l3 = { NULL };

    l1.next = &l2;
    l2.next = &l3;

    printf("%d\n", count_lists(&l1));
    return 0;
}