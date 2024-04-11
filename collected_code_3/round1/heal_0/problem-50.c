#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

int findMinLength(struct Node* head1, struct Node* head2) {
    int count1 = 0, count2 = 0;
    while (head1 != NULL) {
        count1++;
        head1 = head1->next;
    }
    while (head2 != NULL) {
        count2++;
        head2 = head2->next;
    }
    return (count1 < count2) ? count1 : count2;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    printf("Minimum length: %d\n", findMinLength(head1, head2));
    return 0;
}