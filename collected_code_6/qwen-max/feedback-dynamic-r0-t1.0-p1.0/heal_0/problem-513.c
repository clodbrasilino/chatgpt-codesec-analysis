#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *value;
    struct ListNode *next;
} ListNode;

ListNode* append_to_list(ListNode *list, char *data) {
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    if (!new_node) {
        return NULL;
    }
    new_node->value = (char *)malloc(strlen(data) + 1);
    if (!new_node->value) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->value, data);
    new_node->next = list;
    return new_node;
}

ListNode* convert_tuple_to_list(char **tuple, int size, const char *separator) {
    ListNode *list = NULL;
    for (int i = 0; i < size; i++) {
        list = append_to_list(list, tuple[i]);
        if (i < size - 1) {
            list = append_to_list(list, (char *)separator);
        }
    }
    return list;
}

void print_list(ListNode *list) {
    while (list) {
        printf("%s", list->value);
        if (list->next) {
            printf(", ");
        }
        list = list->next;
    }
    printf("\n");
}

void free_list(ListNode *list) {
    while (list) {
        ListNode *temp = list;
        list = list->next;
        free(temp->value);
        free(temp);
    }
}

int main() {
    char *tuple[] = {"a", "b", "c"};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    const char *separator = "X";
    
    ListNode *list = convert_tuple_to_list(tuple, size, separator);
    if (list) {
        print_list(list);
        free_list(list);
    }
    
    return 0;
}