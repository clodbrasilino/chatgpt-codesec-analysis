#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct ListNode {
    char *data;
    struct ListNode *next;
} ListNode;

int all_items_equal(ListNode *head, const char *target) {
    if (target == NULL) {
        return 0;
    }
    
    ListNode *current = head;
    while (current != NULL) {
        if (current->data == NULL || strcmp(current->data, target) != 0) {
            return 0;
        }
        current = current->next;
    }
    
    return 1;
}

ListNode *create_node(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    if (len >= SIZE_MAX) {
        return NULL;
    }
    
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }
    
    node->data = (char *)malloc(len + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(node->data, str, len);
        node->data[len] = '\0';
    } else {
        node->data[0] = '\0';
    }
    node->next = NULL;
    return node;
}

void free_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main(void) {
    ListNode *head = create_node("apple");
    if (head == NULL) {
        return 1;
    }
    
    ListNode *second = create_node("apple");
    if (second == NULL) {
        free_list(head);
        return 1;
    }
    head->next = second;
    
    ListNode *third = create_node("apple");
    if (third == NULL) {
        free_list(head);
        return 1;
    }
    second->next = third;
    
    if (all_items_equal(head, "apple")) {
        printf("All items are equal to 'apple'\n");
    } else {
        printf("Not all items are equal to 'apple'\n");
    }
    
    if (all_items_equal(head, "banana")) {
        printf("All items are equal to 'banana'\n");
    } else {
        printf("Not all items are equal to 'banana'\n");
    }
    
    free_list(head);
    return 0;
}