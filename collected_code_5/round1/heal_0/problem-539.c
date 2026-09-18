#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

Node* create_newnode(double value) {
    Node *newnode = (Node*) malloc(sizeof(Node));
    if(newnode != NULL) {
        newnode->value = value;
        newnode->next = NULL;
    }
    return newnode;
}

void add_end(Node **head, double value) {
    Node *newnode = create_newnode(value);
    if(newnode == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }
    if(*head == NULL) {
        *head = newnode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

void map_powers(double base, int n, Node **output) {
    for(int i = 1; i <= n; i++) {
        double power_value = pow(base, i);
        add_end(output, power_value);
    }
}

void display(Node *head) {
    while (head) {
        printf("%.2f ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main() {
    double base;
    int n;
  
    printf("Enter base: ");
    scanf("%lf", &base);
    printf("Enter length of list: ");
    scanf("%d", &n);
    
    Node* output = NULL;
    map_powers(base, n, &output);
  
    printf("List of powers: ");
    display(output);
  
    return 0;
}