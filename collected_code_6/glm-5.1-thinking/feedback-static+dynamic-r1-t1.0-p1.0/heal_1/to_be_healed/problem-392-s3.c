#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    long long key;
    long long value;
    struct Node *next;
} Node;

#define TABLE_SIZE 10007

Node *memo[TABLE_SIZE];

void free_memo(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *curr = memo[i];
        while (curr != NULL) {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        memo[i] = NULL;
    }
}

long long find_max_sum(long long n) {
    if (n <= 0) {
        return 0;
    }
    if (n < 6) {
        return n;
    }

    unsigned long hash = (unsigned long)n % TABLE_SIZE;
    Node *curr = memo[hash];
    while (curr != NULL) {
        if (curr->key == n) {
            return curr->value;
        }
        curr = curr->next;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 7786195350590628170 + 4714614397334871699 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:334,execs:191,op:havoc,rep:4)
     * UBSan: signed integer overflow: 5921852867245483028 + 4154950881553800643 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:1601,execs:697,op:havoc,rep:4)
     * UBSan: signed integer overflow: 8762773519409443733 + 2316365529566657209 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:334,execs:191,op:havoc,rep:4)
     * UBSan: signed integer overflow: 5757701318346536355 + 3494343368814437927 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:192,execs:125,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8435011612928124701 + 1346047382789966990 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:334,execs:191,op:havoc,rep:4)
     * UBSan: signed integer overflow: 8226523486358938340 + 5757701318346536355 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:192,execs:125,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8859266286050122341 + 1405200995841481409 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:192,execs:125,op:havoc,rep:1)
     * UBSan: signed integer overflow: 5918380645023260806 + 3576286739178380131 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:1601,execs:697,op:havoc,rep:4)
     */
    long long sum = find_max_sum(n / 2) + find_max_sum(n / 3) + find_max_sum(n / 4) + find_max_sum(n / 5);
    long long result = sum > n ? sum : n;

    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return result;
    }
    newNode->key = n;
    newNode->value = result;
    newNode->next = memo[hash];
    memo[hash] = newNode;

    return result;
}

int main(void) {
    long long n;
    if (scanf("%lld", &n) != 1) {
        return 1;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        memo[i] = NULL;
    }

    long long ans = find_max_sum(n);
    printf("%lld\n", ans);

    free_memo();

    return 0;
}