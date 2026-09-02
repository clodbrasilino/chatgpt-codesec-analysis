#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct RLEPair {
    int count;
    int value;
    struct RLEPair *next;
} RLEPair;

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int value) {
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void free_rle_list(RLEPair *head) {
    RLEPair *current = head;
    while (current != NULL) {
        RLEPair *temp = current;
        current = current->next;
        free(temp);
    }
}

RLEPair *create_rle_pair(int count, int value) {
    RLEPair *pair = (RLEPair *)malloc(sizeof(RLEPair));
    if (pair == NULL) {
        return NULL;
    }
    pair->count = count;
    pair->value = value;
    pair->next = NULL;
    return pair;
}

void append_rle_pair(RLEPair **head, int count, int value) {
    RLEPair *new_pair = create_rle_pair(count, value);
    if (new_pair == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_pair;
    } else {
        RLEPair *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_pair;
    }
}

RLEPair *modified_rle_encode(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    
    RLEPair *result = NULL;
    Node *current = head;
    
    while (current != NULL) {
        int count = 1;
        int value = current->value;
        Node *runner = current->next;
        
        while (runner != NULL && runner->value == value) {
            count++;
            runner = runner->next;
        }
        
        if (count > 1) {
            append_rle_pair(&result, count, value);
            current = runner;
        } else {
            Node *single_start = current;
            int single_count = 0;
            Node *temp = current;
            
            while (temp != NULL) {
                if (temp->next != NULL && temp->next->value == temp->value) {
                    break;
                }
                single_count++;
                temp = temp->next;
            }
            
            if (single_count == 1) {
                append_rle_pair(&result, 1, single_start->value);
            } else {
                for (int i = 0; i < single_count; i++) {
                    append_rle_pair(&result, 1, single_start->value);
                    single_start = single_start->next;
                }
            }
            current = temp;
        }
    }
    
    return result;
}

void print_rle_list(RLEPair *head) {
    RLEPair *current = head;
    while (current != NULL) {
        printf("[%d, %d] ", current->count, current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node *list = NULL;
    int numbers[] = {1, 1, 2, 3, 3, 3, 4, 5, 6, 6};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < size; i++) {
        append_node(&list, numbers[i]);
    }
    
    RLEPair *encoded = modified_rle_encode(list);
    print_rle_list(encoded);
    
    free_list(list);
    free_rle_list(encoded);
    
    return 0;
}