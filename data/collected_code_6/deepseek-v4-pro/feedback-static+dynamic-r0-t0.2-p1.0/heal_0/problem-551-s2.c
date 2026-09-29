#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node **children;
    int child_count;
} Node;

int *extract_column(Node *root, int column_index, int *result_size) {
    if (root == NULL || column_index < 0) {
        *result_size = 0;
        return NULL;
    }

    int capacity = 16;
    int size = 0;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    Node **queue = (Node **)malloc(sizeof(Node *));
    if (queue == NULL) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int queue_capacity = 1;
    int queue_size = 0;
    int queue_front = 0;

    queue[queue_size++] = root;

    while (queue_front < queue_size) {
        int level_size = queue_size - queue_front;
        int level_start = queue_front;

        for (int i = 0; i < level_size; i++) {
            Node *current = queue[queue_front++];

            if (i == column_index) {
                if (size >= capacity) {
                    capacity *= 2;
                    int *new_result = (int *)realloc(result, capacity * sizeof(int));
                    if (new_result == NULL) {
                        free(result);
                        free(queue);
                        *result_size = 0;
                        return NULL;
                    }
                    result = new_result;
                }
                result[size++] = current->value;
            }

            for (int j = 0; j < current->child_count; j++) {
                if (queue_size >= queue_capacity) {
                    queue_capacity *= 2;
                    Node **new_queue = (Node **)realloc(queue, queue_capacity * sizeof(Node *));
                    if (new_queue == NULL) {
                        free(result);
                        free(queue);
                        *result_size = 0;
                        return NULL;
                    }
                    queue = new_queue;
                }
                queue[queue_size++] = current->children[j];
            }
        }
    }

    free(queue);
    *result_size = size;
    return result;
}

Node *create_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

int add_child(Node *parent, Node *child) {
    if (parent == NULL || child == NULL) {
        return -1;
    }
    Node **new_children = (Node **)realloc(parent->children, (parent->child_count + 1) * sizeof(Node *));
    if (new_children == NULL) {
        return -1;
    }
    parent->children = new_children;
    parent->children[parent->child_count] = child;
    parent->child_count++;
    return 0;
}

void free_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < root->child_count; i++) {
        free_tree(root->children[i]);
    }
    free(root->children);
    free(root);
}

int main(void) {
    Node *root = create_node(1);
    Node *child1 = create_node(2);
    Node *child2 = create_node(3);
    Node *child3 = create_node(4);
    Node *grandchild1 = create_node(5);
    Node *grandchild2 = create_node(6);
    Node *grandchild3 = create_node(7);
    Node *grandchild4 = create_node(8);

    if (root == NULL || child1 == NULL || child2 == NULL || child3 == NULL ||
        grandchild1 == NULL || grandchild2 == NULL || grandchild3 == NULL || grandchild4 == NULL) {
        free_tree(root);
        free_tree(child1);
        free_tree(child2);
        free_tree(child3);
        free_tree(grandchild1);
        free_tree(grandchild2);
        free_tree(grandchild3);
        free_tree(grandchild4);
        return 1;
    }

    if (add_child(root, child1) != 0 || add_child(root, child2) != 0 || add_child(root, child3) != 0) {
        free_tree(root);
        return 1;
    }

    if (add_child(child1, grandchild1) != 0 || add_child(child1, grandchild2) != 0) {
        free_tree(root);
        return 1;
    }

    if (add_child(child2, grandchild3) != 0) {
        free_tree(root);
        return 1;
    }

    if (add_child(child3, grandchild4) != 0) {
        free_tree(root);
        return 1;
    }

    int result_size = 0;
    int *column = extract_column(root, 1, &result_size);

    if (column != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", column[i]);
        }
        printf("\n");
        free(column);
    }

    free_tree(root);
    return 0;
}