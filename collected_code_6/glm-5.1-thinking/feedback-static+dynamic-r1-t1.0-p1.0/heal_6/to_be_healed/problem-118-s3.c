#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got ["python",""
  */

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    const char *start = str;
    while (*start != '\0') {
        while (isspace((unsigned char)*start)) {
            start++;
        }
        if (*start == '\0') {
            break;
        }

        const char *end = start;
        while (*end != '\0' && !isspace((unsigned char)*end)) {
            end++;
        }

        size_t len = end - start;
        char *word = malloc(len + 1);
        if (word == NULL) {
            free_list(head);
            return NULL;
        }

        for (size_t i = 0; i < len; i++) {
            word[i] = start[i];
        }
        word[len] = '\0';

        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            free(word);
            free_list(head);
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

        start = end;
    }

    return head;
}

void print_list(Node *head) {
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
    fflush(stdout);
}

int main(int argc, const char * const argv[]) {
    char *input = NULL;

    if (argc > 1) {
        size_t total_len = 0;
        for (int i = 1; i < argc; i++) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_len += strlen(argv[i]) + 1;
        }
        input = malloc(total_len + 1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        char *ptr = input;
        for (int i = 1; i < argc; i++) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(argv[i]);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, argv[i], len);
            ptr += len;
            if (i < argc - 1) {
                *ptr = ' ';
                ptr++;
            }
        }
        *ptr = '\0';
    } else {
        size_t buf_size = 4096;
        input = malloc(buf_size);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        if (fgets(input, buf_size, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
        } else {
            input[0] = '\0';
        }
    }

    Node *list = string_to_list(input);
    print_list(list);
    free_list(list);
    free(input);

    return EXIT_SUCCESS;
}