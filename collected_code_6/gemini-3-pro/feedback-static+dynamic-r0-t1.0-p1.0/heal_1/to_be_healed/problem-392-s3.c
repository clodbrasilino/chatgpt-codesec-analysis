#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000003

typedef struct HashNode {
    long long key;
    long long value;
    struct HashNode* next;
} HashNode;

HashNode* hashTable[HASH_SIZE];

void initHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

long long get_val(long long key) {
    int index = key % HASH_SIZE;
    HashNode* curr = hashTable[index];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    return -1;
}

int put_val(long long key, long long value) {
    int index = key % HASH_SIZE;
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (newNode == NULL) {
        return -1;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    return 0;
}

void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = hashTable[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

long long findMaxSum(long long n) {
    if (n == 0) {
        return 0;
    }
    long long val = get_val(n);
    if (val != -1) {
        return val;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 8226523486358938340 + 5757701318346536355 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:759,execs:124,op:havoc,rep:11)
     * UBSan: signed integer overflow: 8398291918862576268 + 2222080357473588128 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:11645,execs:1112,op:havoc,rep:13)
     * UBSan: signed integer overflow: 8984188307715668744 + 5454676890589371449 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:17074,execs:1618,op:havoc,rep:12)
     * UBSan: signed integer overflow: 8762773519409443733 + 2316365529566657209 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:17074,execs:1618,op:havoc,rep:12)
     * UBSan: signed integer overflow: 8435011612928124701 + 1346047382789966990 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:17074,execs:1618,op:havoc,rep:12)
     * UBSan: signed integer overflow: 7450817597811000342 + 4501001037720840323 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:11645,execs:1112,op:havoc,rep:13)
     * UBSan: signed integer overflow: 8859266286050122341 + 1405200995841481409 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:759,execs:124,op:havoc,rep:11)
     * UBSan: signed integer overflow: 5666382357009461871 + 3981334378540040463 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:3905,execs:407,op:havoc,rep:8)
     * UBSan: signed integer overflow: 5757701318346536355 + 3494343368814437927 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:759,execs:124,op:havoc,rep:11)
     * UBSan: signed integer overflow: 8081784121119582512 + 1283111722703545350 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:3905,execs:407,op:havoc,rep:8)
     */
    long long sum = findMaxSum(n / 2) + findMaxSum(n / 3) + findMaxSum(n / 4) + findMaxSum(n / 5);
    long long result = max(sum, n);
    
    if (put_val(n, result) != 0) {
        fprintf(stderr, "Memory allocation failure\n");
        exit(EXIT_FAILURE);
    }
    
    return result;
}

int main() {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    initHashTable();
    
    long long result = findMaxSum(n);
    printf("%lld\n", result);
    
    freeHashTable();
    
    return EXIT_SUCCESS;
}