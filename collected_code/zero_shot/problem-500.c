#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to add a node at the end of the linked list
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

// Function to concatenate all elements of the list into a string
char* concatenateList(struct Node* head) {
    char* result = malloc(1); // Allocate memory for empty string
    result[0] = '\0'; // Initialize empty string

    struct Node* current = head;

    while (current != NULL) {
        int size = snprintf(NULL, 0, "%d", current->data); // Get size of current element
        char* temp = realloc(result, strlen(result) + size + 1); // Resize result string

        if (temp == NULL) {
            free(result);
            return NULL; // Memory allocation failed
        }

        result = temp;
        snprintf(result + strlen(result), size + 1, "%d", current->data); // Append current element to result string
        current = current->next;
    }

    return result;
}

// Main function
int main() {
    struct Node* head = NULL;

    // Add elements to the linked list
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);

    // Concatenate list elements into a string
    char* concatenatedString = concatenateList(head);

    // Print the concatenated string
    printf("%s\n", concatenatedString);

    // Free allocated memory
    free(concatenatedString);

    return 0;
}