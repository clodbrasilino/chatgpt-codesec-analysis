#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const Tuple a, const Tuple b) {
    return (a.first == b.first) && (a.second == b.second);
}

int are_lists_identical(const Tuple *list1, const Tuple *list2, int size) {
    for (int i = 0; i < size; i++) {
        if (!compare_tuples(list1[i], list2[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    printf("Enter the number of tuples: ");
    scanf("%d", &n);

    Tuple *list1 = (Tuple *)malloc(n * sizeof(Tuple));
    Tuple *list2 = (Tuple *)malloc(n * sizeof(Tuple));

    if (list1 == NULL || list2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter elements for the first list (as pairs):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &list1[i].first, &list1[i].second);
    }

    printf("Enter elements for the second list (as pairs):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &list2[i].first, &list2[i].second);
    }

    if (are_lists_identical(list1, list2, n)) {
        printf("The lists are identical.\n");
    } else {
        printf("The lists are not identical.\n");
    }

    free(list1);
    free(list2);
    return 0;
}