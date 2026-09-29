#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 100003

typedef struct Node {
    long long key;
    long long value;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE] = {NULL};

long long get_hash(long long key) {
    return key % HASH_SIZE;
}

long long get_value(long long key) {
    long long hash = get_hash(key);
    Node* current = hashTable[hash];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void insert_value(long long key, long long value) {
    long long hash = get_hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[hash];
    hashTable[hash] = newNode;
}

long long find_max_sum(long long n) {
    if (n == 0) {
        return 0;
    }
    
    long long cached_value = get_value(n);
    if (cached_value != -1) {
        return cached_value;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 8917245553502355884 + 1418202419461905298 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:25206,execs:1694,op:havoc,rep:10)
     * UBSan: signed integer overflow: 5757701318346536355 + 3494343368814437927 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:22012,execs:1484,op:havoc,rep:15)
     * UBSan: signed integer overflow: 8226523486358938340 + 5757701318346536355 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:22012,execs:1484,op:havoc,rep:15)
     * UBSan: signed integer overflow: 7786195350590628170 + 4714614397334871699 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:9038,execs:665,op:havoc,rep:3)
     * UBSan: signed integer overflow: 6281189930271900049 + 4388551362031468981 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:25206,execs:1694,op:havoc,rep:10)
     * UBSan: signed integer overflow: 8435011612928124701 + 1346047382789966990 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:9038,execs:665,op:havoc,rep:3)
     * UBSan: signed integer overflow: 6277544096938566716 + 3814092563558329828 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:25206,execs:1694,op:havoc,rep:10)
     * UBSan: signed integer overflow: 8859266286050122341 + 1405200995841481409 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:22012,execs:1484,op:havoc,rep:15)
     * UBSan: signed integer overflow: 8762773519409443733 + 2316365529566657209 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:9038,execs:665,op:havoc,rep:3)
     */
    long long sum = find_max_sum(n / 2) + find_max_sum(n / 3) + find_max_sum(n / 4) + find_max_sum(n / 5);
    long long max_val = (sum > n) ? sum : n;
    
    insert_value(n, max_val);
    
    return max_val;
}

void free_hash_table() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    long long n;
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    long long result = find_max_sum(n);
    printf("%lld\n", result);
    
    free_hash_table();
    
    return EXIT_SUCCESS;
}