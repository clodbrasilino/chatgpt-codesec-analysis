#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *items;
    int count;
    int capacity;
} PairList;

void initPairList(PairList *list, int capacity) {
    list->items = (Pair*)malloc(capacity * sizeof(Pair));
    list->count = 0;
    list->capacity = capacity;
}

void addPair(PairList *list, int first, int second) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->items = (Pair*)realloc(list->items, list->capacity * sizeof(Pair));
    }
    list->items[list->count].first = first;
    list->items[list->count].second = second;
    list->count++;
}

int containsPair(PairList *list, int first, int second) {
    for (int i = 0; i < list->count; i++) {
        if (list->items[i].first == first && list->items[i].second == second) {
            return 1;
        }
    }
    return 0;
}

int alreadyAdded(PairList *result, int a, int b) {
    return containsPair(result, a, b) || containsPair(result, b, a);
}

PairList findSymmetricPairs(Pair *pairs, int n) {
    PairList result;
    initPairList(&result, 4);
    
    if (n <= 0) {
        return result;
    }
    
    for (int i = 0; i < n; i++) {
        int first = pairs[i].first;
        int second = pairs[i].second;
        
        for (int j = i + 1; j < n; j++) {
            if (pairs[j].first == second && pairs[j].second == first) {
                if (!alreadyAdded(&result, first, second)) {
                    addPair(&result, first, second);
                    addPair(&result, second, first);
                }
                break;
            }
        }
    }
    
    return result;
}

int main() {
    Pair pairs[] = {
        {1, 2}, {2, 1}, {3, 4}, {5, 6}, {4, 3}, {6, 5}, {7, 8}, {8, 9}
    };
    int n = sizeof(pairs) / sizeof(pairs[0]);
    
    PairList result = findSymmetricPairs(pairs, n);
    
    for (int i = 0; i < result.count; i++) {
        printf("(%d, %d) ", result.items[i].first, result.items[i].second);
    }
    printf("\n");
    
    free(result.items);
    return 0;
}