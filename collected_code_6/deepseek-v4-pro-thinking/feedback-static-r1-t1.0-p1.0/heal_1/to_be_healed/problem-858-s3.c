#include <stdio.h>

typedef struct IntList {
    /* Possible weaknesses found:
     *  struct member 'IntList::value' is never used. [unusedStructMember]
     */
    int value;
    /* Possible weaknesses found:
     *  struct member 'IntList::next' is never used. [unusedStructMember]
     */
    struct IntList *next;
} IntList;

typedef struct ListOfLists {
    /* Possible weaknesses found:
     *  struct member 'ListOfLists::list' is never used. [unusedStructMember]
     */
    IntList *list;
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
    IntList n2 = {2, NULL};
    IntList n1 = {1, &n2};

    IntList m1 = {10, NULL};

    ListOfLists outer2 = {&m1, NULL};
    ListOfLists outer1 = {&n1, &outer2};

    printf("%d\n", count_lists_and_square(&outer1));

    return 0;
}