#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    const char *p = str;

    while (*p != '\0') {
        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }

        size_t word_len = p - start;
        char *word = (char *)malloc(word_len + 1);
        if (word == NULL) {
            Node *current = head;
            while (current != NULL) {
                Node *next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            return NULL;
        }
        memcpy(word, start, word_len);
        word[word_len] = '\0';

        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            free(word);
            Node *current = head;
            while (current != NULL) {
                Node *next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            return NULL;
        }

        new_node->data = word;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    if (head == NULL) {
        printf("[]\n");
        return;
    }
    printf("[");
    Node *current = head;
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

int main(void) {
    const char *test1 = "python programming";
    const char *test2 = "lists tuples strings";
    const char *test3 = "write a program";
    
    Node *list1 = string_to_list(test1);
    print_list(list1);
    free_list(list1);
    
    Node *list2 = string_to_list(test2);
    print_list(list2);
    free_list(list2);
    
    Node *list3 = string_to_list(test3);
    print_list(list3);
    free_list(list3);
    
    return 0;
}