#include <stdio.h>
#include <stdlib.h>

int count_and_square_lists(void *list) {
    if (list == NULL) return 0;
    int count = 0;
    for (void **item = (void **)list; *item != NULL; item++) {
        if (*(item + 1) == NULL) {
            count++;
        }
    }
    return count * count;
}

int main() {
    void *list1[] = {(void *)1, (void *)2, NULL};
    void *list2[] = {(void *)3, (void *)4, (void *)5, NULL};
    void *list_of_lists[] = {list1, list2, NULL};

    int result = count_and_square_lists(list_of_lists);
    printf("%d\n", result);

    return 0;
}