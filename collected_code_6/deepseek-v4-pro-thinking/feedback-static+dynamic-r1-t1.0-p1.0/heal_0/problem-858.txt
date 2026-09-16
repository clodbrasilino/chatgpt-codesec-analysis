#include <stdio.h>
#include <stddef.h>

unsigned long long square_list_count(int **lists) {
    size_t count = 0;

    if (lists == NULL) {
        return 0;
    }

    while (lists[count] != NULL) {
        count++;
    }

    return (unsigned long long)count * count;
}

int main(void) {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {6};
    int *lists[] = {list1, list2, list3, NULL};

    printf("%llu\n", square_list_count(lists));
    return 0;
}