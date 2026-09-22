#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    struct list *next;
} List;

int count_and_square_lists(List *head) {
    if (head == NULL) {
        return 0;
    }
    
    int count = 0;
    for (List *current = head; current != NULL; current = current->next) {
        count++;
    }
    
    return count * count;
}

int main() {
    List lists[] = { {&lists[1]}, {&lists[2]}, {&lists[3]}, {NULL} };
    List *head = &lists[0];
    
    int result = count_and_square_lists(head);
    printf("%d\n", result);
    
    return 0;
}