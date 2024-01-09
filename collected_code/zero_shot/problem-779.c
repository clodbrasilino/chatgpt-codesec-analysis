#include <stdio.h>

// structure of a list node
struct Node {
    int data;
    struct Node* next;
};

// function to count the number of unique lists within a list
int countUniqueLists(struct Node* head) {
    int count = 0;
    struct Node* current = head;

    // iterate through the list
    while (current != NULL) {
        struct Node* temp = current->next;

        // iterate through the remaining list nodes
        while (temp != NULL) {
            // check if data of current and temp nodes are the same
            if (current->data == temp->data) {
                // if same, break the loop
                break;
            }
            temp = temp->next;
        }

        // if the end of the second loop is reached, it means the current list is unique
        if (temp == NULL) {
            count++;
        }
        current = current->next;
    }

    return count;
}

// main function for testing
int main() {
    // create a sample list
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 1;
    third->next = NULL;

    // calculate the number of unique lists
    int uniqueLists = countUniqueLists(head);

    // print the result
    printf("Number of unique lists: %d\n", uniqueLists);

    // free memory
    free(head);
    free(second);
    free(third);

    return 0;
}