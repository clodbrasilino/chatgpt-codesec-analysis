#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int normalize(int x, int y, int *nx, int *ny) {
    if (x < y) {
        *nx = x;
        *ny = y;
    } else {
        *nx = y;
        *ny = x;
    }
    return 0;
}

int find_tuple_intersection(Tuple *list1, int len1, Tuple *list2, int len2, Tuple **result, int *res_len) {
    if (!list1 || !list2 || !result || !res_len) {
        return -1;
    }

    int max_len = len1 < len2 ? len1 : len2;
    Tuple *inter = (Tuple *)malloc(max_len * sizeof(Tuple));
    if (!inter) {
        return -1;
    }

    int count = 0;
    for (int i = 0; i < len1; i++) {
        int n1a, n1b;
        normalize(list1[i].a, list1[i].b, &n1a, &n1b);

        for (int j = 0; j < len2; j++) {
            int n2a, n2b;
            normalize(list2[j].a, list2[j].b, &n2a, &n2b);

            if (n1a == n2a && n1b == n2b) {
                int found = 0;
                for (int k = 0; k < count; k++) {
                    if (inter[k].a == n1a && inter[k].b == n1b) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    inter[count].a = n1a;
                    inter[count].b = n1b;
                    count++;
                }
                break;
            }
        }
    }

    if (count == 0) {
        free(inter);
        *result = NULL;
        *res_len = 0;
    } else {
        Tuple *shrunk = (Tuple *)realloc(inter, count * sizeof(Tuple));
        if (shrunk) {
            inter = shrunk;
        }
        *result = inter;
        *res_len = count;
    }

    return 0;
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {2, 1}};
    Tuple list2[] = {{2, 1}, {6, 5}, {7, 8}};
    int len1 = sizeof(list1) / sizeof(list1[0]);
    int len2 = sizeof(list2) / sizeof(list2[0]);

    Tuple *intersection = NULL;
    int inter_len = 0;

    int ret = find_tuple_intersection(list1, len1, list2, len2, &intersection, &inter_len);

    if (ret == 0) {
        for (int i = 0; i < inter_len; i++) {
            printf("(%d, %d)\n", intersection[i].a, intersection[i].b);
        }
        if (intersection) {
            free(intersection);
        }
    }

    return 0;
}