#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

int countNodes(struct Node* head) {
    int count = 0;
    while (head != NULL) {
        head = head->next;
        count++;
    }
    return count;
}

struct Node* findMinLength(struct Node* list1, struct Node* list2) {
    int count1 = countNodes(list1);
    int count2 = countNodes(list2);

    if (count1 < count2)
        return list1;
    else
        return list2;
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    // Populate list1 and list2 with data

    struct Node* minList = findMinLength(list1, list2);

    // Print or use minList as needed

    return 0;
}