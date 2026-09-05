#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node** sublists;
    int* sizes;
    int count;
} SublistCollection;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void free_collection(SublistCollection* collection) {
    if (collection == NULL) {
        return;
    }
    if (collection->sublists != NULL) {
        for (int i = 0; i < collection->count; i++) {
            free_list(collection->sublists[i]);
        }
        free(collection->sublists);
    }
    if (collection->sizes != NULL) {
        free(collection->sizes);
    }
    collection->sublists = NULL;
    collection->sizes = NULL;
    collection->count = 0;
}

int list_length(Node* head) {
    int length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int get_list_elements(Node* head, int* elements, int max_count) {
    if (elements == NULL || max_count < 0) {
        return -1;
    }
    int count = 0;
    Node* current = head;
    while (current != NULL && count < max_count) {
        elements[count] = current->data;
        count++;
        current = current->next;
    }
    return count;
}

Node* create_sublist(const int* elements, int n, unsigned long long mask) {
    if (elements == NULL && n > 0) {
        return NULL;
    }
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        if (mask & (1ULL << i)) {
            Node* node = create_node(elements[i]);
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
    }
    return head;
}

SublistCollection* generate_sublists(Node* head) {
    SublistCollection* collection = (SublistCollection*)malloc(sizeof(SublistCollection));
    if (collection == NULL) {
        return NULL;
    }
    collection->sublists = NULL;
    collection->sizes = NULL;
    collection->count = 0;

    int n = list_length(head);
    if (n > 63) {
        free(collection);
        return NULL;
    }

    unsigned long long total = 1ULL << n;
    if (total > 1000000ULL) {
        free(collection);
        return NULL;
    }

    collection->sublists = (Node**)malloc(total * sizeof(Node*));
    if (collection->sublists == NULL) {
        free(collection);
        return NULL;
    }

    collection->sizes = (int*)malloc(total * sizeof(int));
    if (collection->sizes == NULL) {
        free(collection->sublists);
        free(collection);
        return NULL;
    }

    int* elements = NULL;
    if (n > 0) {
        elements = (int*)malloc(n * sizeof(int));
        if (elements == NULL) {
            free(collection->sizes);
            free(collection->sublists);
            free(collection);
            return NULL;
        }
        if (get_list_elements(head, elements, n) != n) {
            free(elements);
            free(collection->sizes);
            free(collection->sublists);
            free(collection);
            return NULL;
        }
    }

    for (unsigned long long mask = 0; mask < total; mask++) {
        collection->sublists[mask] = create_sublist(elements, n, mask);
        int size = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1ULL << i)) {
                size++;
            }
        }
        collection->sizes[mask] = size;
    }
    collection->count = (int)total;

    if (elements != NULL) {
        free(elements);
    }
    return collection;
}

void print_list(Node* head) {
    Node* current = head;
    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]");
}

void print_sublists(SublistCollection* collection) {
    if (collection == NULL) {
        printf("No sublists\n");
        return;
    }
    printf("Total sublists: %d\n", collection->count);
    for (int i = 0; i < collection->count; i++) {
        printf("Sublist %d: ", i);
        print_list(collection->sublists[i]);
        printf("\n");
    }
}

Node* build_list(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return NULL;
    }
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        Node* node = create_node(arr[i]);
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

int main(void) {
    const int arr[] = {1, 2, 3};
    int n = 3;

    Node* head = build_list(arr, n);
    if (head == NULL) {
        fprintf(stderr, "Failed to build list\n");
        return 1;
    }

    printf("Original list: ");
    print_list(head);
    printf("\n\n");

    SublistCollection* collection = generate_sublists(head);
    if (collection == NULL) {
        fprintf(stderr, "Failed to generate sublists\n");
        free_list(head);
        return 1;
    }

    print_sublists(collection);

    free_collection(collection);
    free_list(head);

    return 0;
}