#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

typedef struct FreqNode {
    int value;
    int count;
    struct FreqNode* next;
} FreqNode;

static Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static List* create_list(void) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->next = NULL;
    return list;
}

static void list_append(List* list, int data) {
    Node* node = create_node(data);
    if (node == NULL) {
        return;
    }
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

static void free_list_nodes(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

static void free_all_lists(List* list_head) {
    List* current = list_head;
    while (current != NULL) {
        List* next = current->next;
        free_list_nodes(current->head);
        free(current);
        current = next;
    }
}

static void free_freq_list(FreqNode* head) {
    FreqNode* current = head;
    while (current != NULL) {
        FreqNode* next = current->next;
        free(current);
        current = next;
    }
}

static FreqNode* find_freq_node(FreqNode* head, int value) {
    FreqNode* current = head;
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static FreqNode* create_freq_node(int value) {
    FreqNode* node = (FreqNode*)malloc(sizeof(FreqNode));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->count = 1;
    node->next = NULL;
    return node;
}

static FreqNode* add_or_update_freq(FreqNode* head, int value) {
    FreqNode* existing = find_freq_node(head, value);
    if (existing != NULL) {
        existing->count++;
        return head;
    }
    
    FreqNode* new_node = create_freq_node(value);
    if (new_node == NULL) {
        return head;
    }
    
    if (head == NULL) {
        return new_node;
    }
    
    new_node->next = head;
    return new_node;
}

FreqNode* frequency_count(List* list_of_lists) {
    FreqNode* freq_head = NULL;
    List* current_list = list_of_lists;
    
    while (current_list != NULL) {
        Node* current_node = current_list->head;
        while (current_node != NULL) {
            freq_head = add_or_update_freq(freq_head, current_node->data);
            if (freq_head == NULL) {
                return NULL;
            }
            current_node = current_node->next;
        }
        current_list = current_list->next;
    }
    
    return freq_head;
}

void print_frequencies(FreqNode* head) {
    FreqNode* current = head;
    while (current != NULL) {
        printf("%d: %d\n", current->value, current->count);
        current = current->next;
    }
}

int main(void) {
    List* list_head = NULL;
    const List* list_tail = NULL;
    
    List* list1 = create_list();
    if (list1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    list_append(list1, 1);
    list_append(list1, 2);
    list_append(list1, 3);
    list_append(list1, 1);
    
    List* list2 = create_list();
    if (list2 == NULL) {
        free_all_lists(list1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    list_append(list2, 2);
    list_append(list2, 3);
    list_append(list2, 4);
    list_append(list2, 2);
    
    List* list3 = create_list();
    if (list3 == NULL) {
        free_all_lists(list1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    list_append(list3, 5);
    list_append(list3, 1);
    list_append(list3, 2);
    list_append(list3, 5);
    list_append(list3, 5);
    
    list_head = list1;
    list1->next = list2;
    list2->next = list3;
    list3->next = NULL;
    list_tail = list3;
    
    FreqNode* frequencies = frequency_count(list_head);
    if (frequencies == NULL) {
        free_all_lists(list_head);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    print_frequencies(frequencies);
    
    free_freq_list(frequencies);
    free_all_lists(list_head);
    
    return 0;
}