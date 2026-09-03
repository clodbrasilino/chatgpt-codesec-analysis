#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *str;
    struct ListNode *next;
} ListNode;

ListNode *create_node(const char *str) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }
    node->str = (char *)malloc(strlen(str) + 1);
    if (node->str == NULL) {
        free(node);
        return NULL;
    }
    strcpy(node->str, str);
    node->next = NULL;
    return node;
}

void free_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

ListNode *string_to_list(const char *input, const char *delimiter) {
    if (input == NULL || delimiter == NULL || delimiter[0] == '\0') {
        return NULL;
    }

    ListNode *head = NULL;
    ListNode *tail = NULL;

    char *input_copy = (char *)malloc(strlen(input) + 1);
    if (input_copy == NULL) {
        return NULL;
    }
    strcpy(input_copy, input);

    char *token = strtok(input_copy, delimiter);
    while (token != NULL) {
        ListNode *node = create_node(token);
        if (node == NULL) {
            free_list(head);
            free(input_copy);
            return NULL;
        }

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        token = strtok(NULL, delimiter);
    }

    free(input_copy);
    return head;
}

void print_list(const ListNode *head) {
    const ListNode *current = head;
    while (current != NULL) {
        printf("%s\n", current->str);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_string> <delimiter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    const char *delimiter = argv[2];

    ListNode *list = string_to_list(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}