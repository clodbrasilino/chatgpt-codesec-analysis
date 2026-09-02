#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    size_t size;
} List;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_destroy(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int list_append(List *list, void *data) {
    if (list == NULL || data == NULL) {
        return -1;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
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

int is_float_convertible(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    char *endptr = NULL;
    errno = 0;
    strtof(str, &endptr);
    
    if (errno == ERANGE) {
        return 0;
    }
    
    if (endptr == str) {
        return 0;
    }
    
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return 0;
        }
        endptr++;
    }
    
    return 1;
}

void convert_to_float(List *list) {
    if (list == NULL) {
        return;
    }
    
    Node *current = list->head;
    while (current != NULL) {
        if (current->data != NULL) {
            char *str_data = (char *)current->data;
            if (is_float_convertible(str_data)) {
                float *float_data = (float *)malloc(sizeof(float));
                if (float_data != NULL) {
                    *float_data = strtof(str_data, NULL);
                    free(current->data);
                    current->data = float_data;
                }
            }
        }
        current = current->next;
    }
}

void print_list(List *list) {
    if (list == NULL) {
        return;
    }
    
    Node *current = list->head;
    while (current != NULL) {
        if (current->data != NULL) {
            char *str_data = (char *)current->data;
            if (is_float_convertible(str_data)) {
                printf("%.2f ", *(float *)current->data);
            } else {
                printf("%s ", str_data);
            }
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List *list = list_create();
    if (list == NULL) {
        return 1;
    }
    
    char *str1 = strdup("3.14");
    char *str2 = strdup("42");
    char *str3 = strdup("hello");
    char *str4 = strdup("2.71828");
    char *str5 = strdup("invalid123");
    char *str6 = strdup("  5.5  ");
    
    if (str1 == NULL || str2 == NULL || str3 == NULL || 
        str4 == NULL || str5 == NULL || str6 == NULL) {
        free(str1);
        free(str2);
        free(str3);
        free(str4);
        free(str5);
        free(str6);
        list_destroy(list);
        return 1;
    }
    
    if (list_append(list, str1) != 0 ||
        list_append(list, str2) != 0 ||
        list_append(list, str3) != 0 ||
        list_append(list, str4) != 0 ||
        list_append(list, str5) != 0 ||
        list_append(list, str6) != 0) {
        free(str1);
        free(str2);
        free(str3);
        free(str4);
        free(str5);
        free(str6);
        list_destroy(list);
        return 1;
    }
    
    printf("Before conversion: ");
    print_list(list);
    
    convert_to_float(list);
    
    printf("After conversion: ");
    print_list(list);
    
    list_destroy(list);
    
    return 0;
}