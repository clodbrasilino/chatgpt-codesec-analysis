#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int data) {
    Node* new_node = create_node(data);
    if (!new_node) {
        return;
    }

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

Node* multiply_lists(Node* list1, Node* list2) {
    if (!list1 || !list2) {
        return NULL;
    }

    int len1 = 0;
    int len2 = 0;
    Node* temp1 = list1;
    Node* temp2 = list2;

    while (temp1 != NULL) {
        len1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        len2++;
        temp2 = temp2->next;
    }

    int* result = (int*)calloc(len1 + len2, sizeof(int));
    if (!result) {
        return NULL;
    }

    int pos1 = 0;

    temp1 = list1;
    while (temp1 != NULL) {
        temp2 = list2;
        int pos2 = 0;

        while (temp2 != NULL) {
            int product = temp1->data * temp2->data;
            int pos = pos1 + pos2;

            result[pos] += product;
            result[pos + 1] += result[pos] / 10;
            result[pos] %= 10;

            temp2 = temp2->next;
            pos2++;
        }
        temp1 = temp1->next;
        pos1++;
    }

    int total_len = len1 + len2;
    while (total_len > 1 && result[total_len - 1] == 0) {
        total_len--;
    }

    Node* result_head = NULL;
    for (int i = total_len - 1; i >= 0; i--) {
        append_node(&result_head, result[i]);
    }

    free(result);
    return result_head;
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    append_node(&list1, 3);
    append_node(&list1, 4);
    append_node(&list1, 2);

    append_node(&list2, 4);
    append_node(&list2, 6);
    append_node(&list2, 5);

    result = multiply_lists(list1, list2);

    if (result != NULL) {
        Node* current = result;
        while (current != NULL) {
            printf("%d", current->data);
            if (current->next != NULL) {
                printf(" -> ");
            }
            current = current->next;
        }
        printf("\n");
    }

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}