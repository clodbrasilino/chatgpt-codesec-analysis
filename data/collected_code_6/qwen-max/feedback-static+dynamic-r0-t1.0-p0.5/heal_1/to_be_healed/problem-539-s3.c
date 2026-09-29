#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->value = value;
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

Node* map_power(Node *base, Node *index) {
    if (base == NULL || index == NULL) return NULL;
    
    Node *result = NULL;
    Node *tail = NULL;
    Node *b = base;
    Node *i = index;
    
    while (b != NULL && i != NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         */
        Node *new_node = create_node(pow(b->value, i->value));
        if (new_node == NULL) {
            free_list(result);
            return NULL;
        }
        if (result == NULL) {
            result = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        b = b->next;
        i = i->next;
    }
    
    return result;
}

int main() {
    Node *base = create_node(2);
    base->next = create_node(3);
    base->next->next = create_node(4);

    Node *index = create_node(1);
    index->next = create_node(2);
    index->next->next = create_node(3);

    Node *result = map_power(base, index);

    Node *current = result;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    free_list(base);
    free_list(index);
    free_list(result);

    return 0;
}