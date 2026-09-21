#include <stdio.h>
#include <stdlib.h>

struct Node {
    char* data;
    struct Node* next;
};

char* concatenate_list(struct Node* head) {
    if (head == NULL) {
        char* empty_str = (char*)malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    struct Node* current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            const char* ptr = current->data;
            while (*ptr != '\0') {
                total_length++;
                ptr++;
            }
        }
        current = current->next;
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* current_dest = result;
    size_t remaining = total_length;
    current = head;
    
    while (current != NULL) {
        if (current->data != NULL) {
            const char* ptr = current->data;
            while (*ptr != '\0' && remaining > 0) {
                *current_dest = *ptr;
                current_dest++;
                ptr++;
                remaining--;
            }
        }
        current = current->next;
    }
    *current_dest = '\0';

    return result;
}

void free_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
    if (node1 == NULL) return 1;
    node1->data = "Hello";
    
    struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
    if (node2 == NULL) {
        free(node1);
        return 1;
    }
    node2->data = ", ";
    
    struct Node* node3 = (struct Node*)malloc(sizeof(struct Node));
    if (node3 == NULL) {
        free(node1);
        free(node2);
        return 1;
    }
    node3->data = "World!";
    node3->next = NULL;

    node1->next = node2;
    node2->next = node3;

    char* concatenated_string = concatenate_list(node1);
    
    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        printf("Failed to concatenate list.\n");
    }

    free_list(node1);

    return 0;
}