#include <stdio.h>
#include <stdlib.h>

typedef int (*Comparator)(const void *, const void *);

typedef struct Node {
    void *value;
    struct Node *next;
} Node;

typedef struct Iterator {
    Node *(*next)(Node **);
    int has_next;
} Iterator;

typedef struct PriorityQueue {
    Node **nodes;
    int size;
    int capacity;
    Comparator cmp;
} PriorityQueue;

Node *iterator_next(Node **head) {
    if (*head != NULL) {
        Node *current = *head;
        *head = current->next;
        return current;
    }
    return NULL;
}

Iterator create_iterator(const Node *head) {
    Iterator it = {0};
    it.has_next = head != NULL;
    it.next = iterator_next;
    return it;
}

PriorityQueue *create_pqueue(Comparator cmp, int initial_capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->nodes = calloc(initial_capacity, sizeof(Node *));
    pq->size = 0;
    pq->capacity = initial_capacity;
    pq->cmp = cmp;
    return pq;
}

void insert(PriorityQueue *pq, Node *node) {
    if (pq->size >= pq->capacity) {
        pq->nodes = realloc(pq->nodes, 2 * pq->capacity * sizeof(Node *));
        pq->capacity *= 2;
    }
    pq->nodes[pq->size++] = node;
    int i = pq->size - 1;
    while (i > 0 && pq->cmp(pq->nodes[i]->value, pq->nodes[(i - 1) / 2]->value) < 0) {
        Node *temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        pq->nodes[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node *extract_min(PriorityQueue *pq) {
    if (pq->size == 0) {
        return NULL;
    }
    Node *min_node = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0;
    while (2 * i + 1 < pq->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < pq->size && pq->cmp(pq->nodes[right]->value, pq->nodes[left]->value) < 0) {
            j = right;
        }
        if (pq->cmp(pq->nodes[i]->value, pq->nodes[j]->value) <= 0) {
            break;
        }
        Node *temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[j];
        pq->nodes[j] = temp;
        i = j;
    }
    return min_node;
}

void free_pqueue(PriorityQueue *pq) {
    for (int i = 0; i < pq->size; i++) {
        free(pq->nodes[i]->value);
        free(pq->nodes[i]);
    }
    free(pq->nodes);
    free(pq);
}

int compare_int(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

Node *merge_sorted_iterators(const Iterator *iterators, int count) {
    PriorityQueue *pq = create_pqueue((Comparator)compare_int, count);
    Node **heads = malloc(count * sizeof(Node *));
    for (int i = 0; i < count; i++) {
        Node *head = NULL;
        heads[i] = iterators[i].next(&head);
        iterators[i].has_next = head != NULL;
        if (heads[i] != NULL) {
            insert(pq, heads[i]);
        }
    }

    Node *head = NULL;
    Node **tail = &head;
    while (pq->size > 0) {
        Node *min_node = extract_min(pq);
        *tail = min_node;
        tail = &(*tail)->next;

        for (int i = 0; i < count; i++) {
            if (heads[i] == min_node) {
                Node *new_head = NULL;
                heads[i] = iterators[i].next(&new_head);
                iterators[i].has_next = new_head != NULL;
                if (heads[i] != NULL) {
                    insert(pq, heads[i]);
                }
            }
        }
    }
    *tail = NULL;
    free(heads);
    free_pqueue(pq);
    return head;
}

void print_list(Node *head) {
    for (Node *current = head; current != NULL; current = current->next) {
        printf("%d ", *(int *)current->value);
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

int main() {
    int a1 = 1;
    int a2 = 3;
    int a3 = 5;
    int a4 = 7;
    const Node n1_2 = {.value = &a2, .next = (Node *)&((Node){.value = &a3, .next = (Node *)&((Node){.value = &a4, .next = NULL})})};
    const Node n1_1 = {.value = &a1, .next = &n1_2};
    const Node *list1 = &n1_1;

    int b1 = 2;
    int b2 = 4;
    int b3 = 6;
    int b4 = 8;
    const Node n2_2 = {.value = &b2, .next = (Node *)&((Node){.value = &b3, .next = (Node *)&((Node){.value = &b4, .next = NULL})})};
    const Node n2_1 = {.value = &b1, .next = &n2_2};
    const Node *list2 = &n2_1;

    const Iterator it1 = create_iterator(list1);
    const Iterator it2 = create_iterator(list2);
    const Iterator iterators[] = {it1, it2};

    Node *merged_list = merge_sorted_iterators(iterators, 2);
    print_list(merged_list);
    free_list(merged_list);

    return 0;
}