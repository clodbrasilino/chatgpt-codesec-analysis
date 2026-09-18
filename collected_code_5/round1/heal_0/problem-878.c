#include <stdio.h>
#include <stdbool.h>

bool check_elements(int tuple[], int size, int k) {
    return size == k;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int k = 5;

    if (check_elements(tuple, sizeof(tuple)/sizeof(tuple[0]), k))
        printf("The tuple contains exactly %d elements.\n", k);
    else
        printf("The tuple does not contain exactly %d elements.\n", k);

    return 0;
}