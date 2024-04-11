#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

int findMaxLength(struct Node* list1, struct Node* list2) {
    int len1 = 0, len2 = 0;
    while(list1 != NULL) {
        len1++;
        list1 = list1->next;
    }
    while(list2 != NULL) {
        len2++;
        list2 = list2->next;
    }
    return (len1 > len2) ? len1 : len2;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    int maxLength = findMaxLength(head1, head2);
    printf("Maximum length: %d\n", maxLength);
    return 0;
}