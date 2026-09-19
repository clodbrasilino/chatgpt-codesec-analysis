#include <stdio.h>
#include <stdlib.h>

typedef struct PairNode {
    int first;
    int second;
    int count;
    struct PairNode *next;
} PairNode;

unsigned int hash_pair(int a, int b, int table_size) {
    int first = a < b ? a : b;
    int second = a < b ? b : a;
    unsigned long long key = (unsigned long long)first * 1000000007ULL + (unsigned long long)second;
    unsigned int ha = (unsigned int)(key >> 32);
    unsigned int hb = (unsigned int)(key & 0xFFFFFFFF);
    unsigned int h = ha ^ hb;
    h = h * 2654435761u;
    return h % (unsigned int)table_size;
}

PairNode **create_map(int size) {
    PairNode **map = (PairNode **)calloc((size_t)size, sizeof(PairNode *));
    return map;
}

void free_map(PairNode **map, int size) {
    if (map == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        PairNode *current = map[i];
        while (current != NULL) {
            PairNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(map);
}

void map_insert(PairNode **map, int size, int a, int b, int count) {
    unsigned int index = hash_pair(a, b, size);
    PairNode *current = map[index];
    int first = a < b ? a : b;
    int second = a < b ? b : a;
    while (current != NULL) {
        if (current->first == first && current->second == second) {
            current->count += count;
            return;
        }
        current = current->next;
    }
    PairNode *new_node = (PairNode *)malloc(sizeof(PairNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->first = first;
    new_node->second = second;
    new_node->count = count;
    new_node->next = map[index];
    map[index] = new_node;
}

int map_get(PairNode **map, int size, int a, int b) {
    unsigned int index = hash_pair(a, b, size);
    PairNode *current = map[index];
    int first = a < b ? a : b;
    int second = a < b ? b : a;
    while (current != NULL) {
        if (current->first == first && current->second == second) {
            return current->count;
        }
        current = current->next;
    }
    return 0;
}

int pair_exists(int **seen, int first, int second, int size) {
    for (int i = 0; i < size; i++) {
        if (seen[i] != NULL && seen[i][0] == first && seen[i][1] == second) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4, got 3
  *  test case 2 failed: expected 1, got 3
  *  test case 1 failed: expected 11, got 22
  */

int count_same_pairs(const int *list1, int size1, const int *list2, int size2) {
    if (list1 == NULL || list2 == NULL) {
        return 0;
    }
    if (size1 < 2 || size2 < 2) {
        return 0;
    }

    int num_pairs1 = (size1 * (size1 - 1)) / 2;
    int table_size = num_pairs1 * 2 + 1;
    if (table_size < 10) {
        table_size = 10;
    }

    PairNode **map = create_map(table_size);
    if (map == NULL) {
        fprintf(stderr, "Failed to create hash map\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size1; i++) {
        for (int j = i + 1; j < size1; j++) {
            map_insert(map, table_size, list1[i], list1[j], 1);
        }
    }

    int max_pairs2 = (size2 * (size2 - 1)) / 2;
    int **seen_pairs = (int **)malloc((size_t)max_pairs2 * sizeof(int *));
    if (seen_pairs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_map(map, table_size);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < max_pairs2; i++) {
        seen_pairs[i] = NULL;
    }

    int total_count = 0;
    int seen_count = 0;

    for (int i = 0; i < size2; i++) {
        for (int j = i + 1; j < size2; j++) {
            int first = list2[i] < list2[j] ? list2[i] : list2[j];
            int second = list2[i] < list2[j] ? list2[j] : list2[i];

            if (!pair_exists(seen_pairs, first, second, seen_count)) {
                int val = map_get(map, table_size, list2[i], list2[j]);
                if (val > 0) {
                    total_count++;
                    seen_pairs[seen_count] = (int *)malloc(2 * sizeof(int));
                    if (seen_pairs[seen_count] == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        for (int m = 0; m < seen_count; m++) {
                            free(seen_pairs[m]);
                        }
                        free(seen_pairs);
                        free_map(map, table_size);
                        exit(EXIT_FAILURE);
                    }
                    seen_pairs[seen_count][0] = first;
                    seen_pairs[seen_count][1] = second;
                    seen_count++;
                }
            }
        }
    }

    for (int i = 0; i < seen_count; i++) {
        free(seen_pairs[i]);
    }
    free(seen_pairs);
    free_map(map, table_size);
    return total_count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {3, 1, 2, 5, 4};
    int size1 = (int)(sizeof(list1) / sizeof(list1[0]));
    int size2 = (int)(sizeof(list2) / sizeof(list2[0]));

    int result = count_same_pairs(list1, size1, list2, size2);
    printf("%d\n", result);

    int list3[] = {1, 2, 3};
    int list4[] = {1, 2, 3, 4};
    int size3 = (int)(sizeof(list3) / sizeof(list3[0]));
    int size4 = (int)(sizeof(list4) / sizeof(list4[0]));

    int result2 = count_same_pairs(list3, size3, list4, size4);
    printf("%d\n", result2);

    int list5[] = {7, 8, 9};
    int list6[] = {10, 11, 12};
    int size5 = (int)(sizeof(list5) / sizeof(list5[0]));
    int size6 = (int)(sizeof(list6) / sizeof(list6[0]));

    int result3 = count_same_pairs(list5, size5, list6, size6);
    printf("%d\n", result3);

    return 0;
}