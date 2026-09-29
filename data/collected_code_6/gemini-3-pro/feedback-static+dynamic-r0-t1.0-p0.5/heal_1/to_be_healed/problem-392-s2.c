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
     * UBSan: signed integer overflow: 5757701318346536355 + 3494343368814437927 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:9902,execs:858,op:havoc,rep:1)
     * UBSan: signed integer overflow: 7450817597811000342 + 4501001037720840323 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:29744,execs:2288,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8226523486358938340 + 5757701318346536355 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:9902,execs:858,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8081784121119582512 + 1283111722703545350 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:29744,execs:2288,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8398291918862576268 + 2222080357473588128 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:29744,execs:2288,op:havoc,rep:1)
     * UBSan: signed integer overflow: 5666382357009461868 + 3981334378540040463 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:31006,execs:2370,op:havoc,rep:2)
     * UBSan: signed integer overflow: 8859266286050122341 + 1405200995841481409 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:9902,execs:858,op:havoc,rep:1)
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