#include <stdio.h>
#include <stdlib.h>

int count_and_square_lists(void *list) {
    int count = 0;
    for (void **item = (void **)list; *item != NULL; item++) {
        if (*(void **)*item != NULL) {
            count++;
        }
    }
    return count * count;
}

int main() {
    void *list1[] = {NULL, NULL, NULL};
    void *list2[] = {&list1, &list1, NULL};
    void *list3[] = {&list2, &list2, &list2, NULL};

    printf("%d\n", count_and_square_lists(list3));
    return 0;
}