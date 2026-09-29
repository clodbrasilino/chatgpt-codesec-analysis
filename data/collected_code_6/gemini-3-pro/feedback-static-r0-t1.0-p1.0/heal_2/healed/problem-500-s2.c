#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

struct Node {
    char* data;
    struct Node* next;
};

static size_t safe_strlen(const char* str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_list(struct Node* head) {
    if (head == NULL) {
        char* empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    struct Node* current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            total_length += safe_strlen(current->data, MAX_STR_LEN);
        }
        current = current->next;
    }

    char* result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* dest = result;
    size_t remaining_size = total_length + 1;
    current = head;
    
    while (current != NULL) {
        if (current->data != NULL) {
            size_t len = safe_strlen(current->data, MAX_STR_LEN);
            if (len < remaining_size) {
                memcpy(dest, current->data, len);
                dest += len;
                remaining_size -= len;
            }
        }
        current = current->next;
    }
    *dest = '\0';

    return result;
}

int main(void) {
    struct Node node3 = {"World!", NULL};
    struct Node node2 = {" ", &node3};
    struct Node node1 = {"Hello", &node2};

    char* concatenated_string = concatenate_list(&node1);

    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    return 0;
}