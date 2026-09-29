#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct RLE_Node {
    int count;
    char data;
    struct RLE_Node* next;
} RLE_Node;

Node* create_node(char data);
RLE_Node* create_rle_node(int count, char data);
void free_list(Node* head);
void free_rle_list(RLE_Node* head);
RLE_Node* modified_rle(Node* head);
void print_rle_list(RLE_Node* head);

Node* create_node(char data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

RLE_Node* create_rle_node(int count, char data) {
    RLE_Node* new_node = (RLE_Node*)malloc(sizeof(RLE_Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->count = count;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_rle_list(RLE_Node* head) {
    while (head) {
        RLE_Node* temp = head;
        head = head->next;
        free(temp);
    }
}

RLE_Node* modified_rle(Node* head) {
    if (!head) {
        return NULL;
    }

    RLE_Node* rle_head = NULL;
    RLE_Node* rle_tail = NULL;

    char current_char = head->data;
    int count = 1;
    Node* curr = head->next;

    while (curr) {
        if (curr->data == current_char) {
            count++;
        } else {
            RLE_Node* new_rle = create_rle_node(count, current_char);
            if (!rle_head) {
                rle_head = new_rle;
                rle_tail = rle_head;
            } else {
                rle_tail->next = new_rle;
                rle_tail = new_rle;
            }
            current_char = curr->data;
            count = 1;
        }
        curr = curr->next;
    }

    RLE_Node* new_rle = create_rle_node(count, current_char);
    if (!rle_head) {
        rle_head = new_rle;
    } else {
        rle_tail->next = new_rle;
    }

    return rle_head;
}

void print_rle_list(RLE_Node* head) {
    while (head) {
        if (head->count > 1) {
            printf("(%d, %c) ", head->count, head->data);
        } else {
            printf("%c ", head->data);
        }
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    char data[] = {'a', 'a', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'd', 'e', 'e', 'e', 'e'};
    size_t size = sizeof(data) / sizeof(data[0]);

    Node* head = create_node(data[0]);
    Node* tail = head;
    
    for (size_t i = 1; i < size; ++i) {
        tail->next = create_node(data[i]);
        tail = tail->next;
    }

    RLE_Node* rle_head = modified_rle(head);
    
    print_rle_list(rle_head);

    free_list(head);
    free_rle_list(rle_head);

    return EXIT_SUCCESS;
}