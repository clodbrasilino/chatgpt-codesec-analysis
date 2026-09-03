#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data);
Node *create_list_from_array(int *array, int size);
int contains(Node *head, int value);
int list_subtract(Node *list1, Node *list2, Node **result);
void free_list(Node *head);
void print_list(Node *head);

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
Node *create_list_from_array(int *array, int size) {
    Node *head = NULL;
    Node *tail = NULL;
    int i;
    for (i = 0; i < size; i++) {
        Node *node = create_node(array[i]);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

int contains(Node *head, int value) {
    while (head != NULL) {
        if (head->data == value) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

int list_subtract(Node *list1, Node *list2, Node **result) {
    if (result == NULL) {
        return -1;
    }
    *result = NULL;
    Node *head = NULL;
    Node *tail = NULL;
    Node *current = list1;
    while (current != NULL) {
        if (!contains(list2, current->data)) {
            Node *node = create_node(current->data);
            if (node == NULL) {
                free_list(head);
                *result = NULL;
                return -1;
            }
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
        current = current->next;
    }
    *result = head;
    return 0;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 4, 6};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    Node *list1 = create_list_from_array(arr1, size1);
    Node *list2 = create_list_from_array(arr2, size2);

    if (list1 == NULL || list2 == NULL) {
        free_list(list1);
        free_list(list2);
        return 1;
    }

    Node *result = NULL;
    int status = list_subtract(list1, list2, &result);
    if (status != 0) {
        free_list(list1);
        free_list(list2);
        return 1;
    }

    if (result == NULL) {
        printf("Result is empty.\n");
    } else {
        print_list(result);
    }

    free_list(result);
    free_list(list1);
    free_list(list2);

    return 0;
}