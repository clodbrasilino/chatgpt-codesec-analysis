#include <stdio.h>

typedef struct IntList {
    /* Possible weaknesses found:
     *  struct member 'IntList::next' is never used. [unusedStructMember]
     */
    struct IntList *next;
} IntList;

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
    IntList n2 = {NULL};
    /* Possible weaknesses found:
     *  Value stored to 'n1' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'n1' is assigned a value that is never used. [unreadVariable]
     */
    IntList n1 = {&n2};

    /* Possible weaknesses found:
     *  Variable 'm1' is assigned a value that is never used. [unreadVariable]
     */
    IntList m1 = {NULL};

    ListOfLists outer2 = {NULL};
    ListOfLists outer1 = {&outer2};

    printf("%d\n", count_lists_and_square(&outer1));

    return 0;
}