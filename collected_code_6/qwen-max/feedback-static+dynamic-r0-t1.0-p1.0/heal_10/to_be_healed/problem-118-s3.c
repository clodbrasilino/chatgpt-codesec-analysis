#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* create_node(const char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->data = strdup(data);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void delete_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

Node* string_to_list(const char* str, const char* delimiter) {
    char *copy = strdup(str);
    if (copy == NULL) return NULL;

    char *token = strtok(copy, delimiter);
    Node* head = NULL;
    Node* tail = NULL;

    while (token != NULL) {
        Node* new_node = create_node(token);
        if (new_node == NULL) {
            delete_list(head);
            free(copy);
            return NULL;
        }

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        token = strtok(NULL, delimiter);
    }

    free(copy);
    return head;
}

int main() {
    const char* input1 = "python,programming";
    const char* delimiter1 = ",";
    Node* list1 = string_to_list(input1, delimiter1);
    if (list1 == NULL) {
        printf("Failed to convert string to list\n");
        return 1;
    }
    Node* current1 = list1;
    while (current1 != NULL) {
        printf("%s\n", current1->data);
        current1 = current1->next;
    }
    delete_list(list1);

    const char* input2 = "lists,tuples,strings";
    const char* delimiter2 = ",";
    Node* list2 = string_to_list(input2, delimiter2);
    if (list2 == NULL) {
        printf("Failed to convert string to list\n");
        return 1;
    }
    Node* current2 = list2;
    while (current2 != NULL) {
        printf("%s\n", current2->data);
        current2 = current2->next;
    }
    delete_list(list2);

    const char* input3 = "write,a,program";
    const char* delimiter3 = ",";
    Node* list3 = string_to_list(input3, delimiter3);
    if (list3 == NULL) {
        printf("Failed to convert string to list\n");
        return 1;
    }
    Node* current3 = list3;
    while (current3 != NULL) {
        printf("%s\n", current3->data);
        current3 = current3->next;
    }
    delete_list(list3);

    return 0;
}