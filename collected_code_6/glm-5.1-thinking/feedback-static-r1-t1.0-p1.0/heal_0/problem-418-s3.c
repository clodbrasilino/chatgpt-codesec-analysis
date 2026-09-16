#include <stdio.h>
#include <stdlib.h>

typedef struct SubListNode {
    int data;
    struct SubListNode *next;
} SubListNode;

typedef struct MainListNode {
    SubListNode *sublist;
    struct MainListNode *next;
} MainListNode;

int get_sublist_length(SubListNode *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

SubListNode *find_max_length_sublist(MainListNode *head) {
    if (head == NULL) {
        return NULL;
    }

    SubListNode *max_sublist = head->sublist;
    int max_length = get_sublist_length(head->sublist);

    MainListNode *current = head->next;
    while (current != NULL) {
        int current_length = get_sublist_length(current->sublist);
        if (current_length > max_length) {
            max_length = current_length;
            max_sublist = current->sublist;
        }
        current = current->next;
    }

    return max_sublist;
}

SubListNode *create_sublist_node(int data) {
    SubListNode *node = malloc(sizeof(SubListNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

MainListNode *create_main_list_node(SubListNode *sublist) {
    MainListNode *node = malloc(sizeof(MainListNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->sublist = sublist;
    node->next = NULL;
    return node;
}

void free_sublist(SubListNode *head) {
    SubListNode *current = head;
    while (current != NULL) {
        SubListNode *next = current->next;
        free(current);
        current = next;
    }
}

void free_main_list(MainListNode *head) {
    MainListNode *current = head;
    while (current != NULL) {
        MainListNode *next = current->next;
        free_sublist(current->sublist);
        free(current);
        current = next;
    }
}

void print_sublist(SubListNode *head) {
    SubListNode *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    SubListNode *sublist1 = create_sublist_node(1);
    sublist1->next = create_sublist_node(2);

    SubListNode *sublist2 = create_sublist_node(3);
    sublist2->next = create_sublist_node(4);
    sublist2->next->next = create_sublist_node(5);

    SubListNode *sublist3 = create_sublist_node(6);

    MainListNode *main_list = create_main_list_node(sublist1);
    main_list->next = create_main_list_node(sublist2);
    main_list->next->next = create_main_list_node(sublist3);

    SubListNode *max_sublist = find_max_length_sublist(main_list);
    if (max_sublist != NULL) {
        printf("Maximum length sublist: ");
        print_sublist(max_sublist);
    } else {
        printf("The list is empty.\n");
    }

    free_main_list(main_list);

    return 0;
}