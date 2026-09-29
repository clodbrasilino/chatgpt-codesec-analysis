#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

Node* create_node(char c);
void free_list(Node *head);
Node* string_to_list(const char *str);

Node* create_node(char c) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = c;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node* string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    for (size_t i = 0; str[i] != '\0'; i++) {
        Node *new_node = create_node(str[i]);
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return head;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'sample_text="Secure C Programming"', assigned value is "Secure C Programming"
     */
    const char *sample_text = "Secure C Programming";
    
    Node *list_head = string_to_list(sample_text);
    /* Possible weaknesses found:
     *  Condition 'sample_text[0]!='\0'' is always true [knownConditionTrueFalse]
     *  Condition 'sample_text[0]!='\0'' is always true
     */
    if (list_head == NULL && sample_text[0] != '\0') {
        return EXIT_FAILURE;
    }

    Node *current = list_head;
    while (current != NULL) {
        putchar(current->data);
        current = current->next;
    }
    putchar('\n');

    free_list(list_head);

    return EXIT_SUCCESS;
}