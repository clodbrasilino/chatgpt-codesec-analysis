#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

List *create_list(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void destroy_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int append_node(List *list, int value) {
    if (list == NULL) {
        return -1;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = value;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 0;
}

void remove_duplicates_from_list(List *list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    
    Node *current = list->head;
    while (current != NULL && current->next != NULL) {
        Node *runner = current;
        while (runner->next != NULL) {
            if (runner->next->data == current->data) {
                Node *duplicate = runner->next;
                runner->next = duplicate->next;
                free(duplicate);
                list->size--;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

void remove_two_duplicates_from_lists(List **lists, int num_lists) {
    if (lists == NULL || num_lists <= 0) {
        return;
    }
    
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            remove_duplicates_from_list(lists[i]);
        }
    }
}

void print_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int num_lists = 3;
    List **lists = (List **)malloc(num_lists * sizeof(List *));
    if (lists == NULL) {
        return 1;
    }
    
    for (int i = 0; i < num_lists; i++) {
        lists[i] = create_list();
        if (lists[i] == NULL) {
            for (int j = 0; j < i; j++) {
                destroy_list(lists[j]);
            }
            free(lists);
            return 1;
        }
    }
    
    int test_data[3][6] = {
        {1, 2, 2, 3, 4, 4},
        {5, 5, 6, 7, 7, 8},
        {9, 10, 10, 11, 12, 12}
    };
    
    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < 6; j++) {
            if (append_node(lists[i], test_data[i][j]) != 0) {
                for (int k = 0; k < num_lists; k++) {
                    destroy_list(lists[k]);
                }
                free(lists);
                return 1;
            }
        }
    }
    
    printf("Original lists:\n");
    for (int i = 0; i < num_lists; i++) {
        printf("List %d: ", i + 1);
        print_list(lists[i]);
    }
    
    remove_two_duplicates_from_lists(lists, num_lists);
    
    printf("\nLists after removing duplicates:\n");
    for (int i = 0; i < num_lists; i++) {
        printf("List %d: ", i + 1);
        print_list(lists[i]);
    }
    
    for (int i = 0; i < num_lists; i++) {
        destroy_list(lists[i]);
    }
    free(lists);
    
    return 0;
}