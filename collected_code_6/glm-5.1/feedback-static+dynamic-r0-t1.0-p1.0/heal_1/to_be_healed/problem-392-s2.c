#include <stdio.h>
#include <stdlib.h>

struct Node {
    long long key;
    long long value;
    struct Node *next;
};

#define TABLE_SIZE 1000003

struct Node *hash_table[TABLE_SIZE];

long long find_max_sum(long long n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long hash = (unsigned long long)n % TABLE_SIZE;
    struct Node *current = hash_table[hash];
    while (current != NULL) {
        if (current->key == n) {
            return current->value;
        }
        current = current->next;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 5666382357009461868 + 3981334378540040463 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:37815,execs:2341,op:havoc,rep:1)
     * UBSan: signed integer overflow: 7450817597811000342 + 4501001037720840323 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:14363,execs:890,op:havoc,rep:2)
     * UBSan: signed integer overflow: 8226523486358938340 + 5757701318346536355 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:2701,execs:181,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8398291918862576268 + 2222080357473588128 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:14363,execs:890,op:havoc,rep:2)
     * UBSan: signed integer overflow: 8762773519409443733 + 2316365529566657209 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:18592,execs:1148,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8859266286050122341 + 1405200995841481409 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:2701,execs:181,op:havoc,rep:1)
     * UBSan: signed integer overflow: 5757701318346536355 + 3494343368814437927 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:2701,execs:181,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8984188307715668744 + 5454676890589371449 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:18592,execs:1148,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8435011612928124701 + 1346047382789966990 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:18592,execs:1148,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8081784121119582512 + 1283111722703545350 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:14363,execs:890,op:havoc,rep:2)
     */
    long long sum = find_max_sum(n / 2) + find_max_sum(n / 3) + find_max_sum(n / 4) + find_max_sum(n / 5);
    long long result = (sum > n) ? sum : n;

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->key = n;
    new_node->value = result;
    new_node->next = hash_table[hash];
    hash_table[hash] = new_node;

    return result;
}

void free_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node *current = hash_table[i];
        while (current != NULL) {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }

    long long n;
    if (scanf("%lld", &n) == 1) {
        printf("%lld\n", find_max_sum(n));
    }

    free_hash_table();
    return 0;
}