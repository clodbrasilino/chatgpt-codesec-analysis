#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef struct Tuple {
    long long first;
    long long second;
    struct Tuple *next;
} Tuple;

static int sum_alternate_chains(const Tuple *head, long long *first_sum,
                                long long *second_sum)
{
    size_t index = 0;
    long long even_sum = 0;
    long long odd_sum = 0;

    if (first_sum == NULL || second_sum == NULL) {
        return -1;
    }

    while (head != NULL) {
        /* Possible weaknesses found:
         *  value is initialized
         * UBSan: signed integer overflow: 9223372036854775807 + 9 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000011,time:9593,execs:5116,op:havoc,rep:1)
         * UBSan: signed integer overflow: 7 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000020,time:39343,execs:20610,op:havoc,rep:3)
         * UBSan: signed integer overflow: 6 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000011,time:9915,execs:5274,op:havoc,rep:2)
         * UBSan: signed integer overflow: 9223372036854775807 + 6 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000016,time:21032,execs:11009,op:havoc,rep:1)
         *  Value stored to 'value' during its initialization is never read [deadcode.DeadStores]
         * UBSan: signed integer overflow: 8 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000008,time:7103,execs:3864,op:havoc,rep:1)
         */
        long long value = head->first + head->second;

        if ((head->second > 0 && head->first > LLONG_MAX - head->second) ||
            (head->second < 0 && head->first < LLONG_MIN - head->second)) {
            return -1;
        }

        /* Possible weaknesses found:
         *  Redundant initialization for 'value'. The initialized value is overwritten before it is read. [redundantInitialization]
         *  value is overwritten
         */
        value = head->first + head->second;

        if ((index % 2U) == 0U) {
            if ((value > 0 && even_sum > LLONG_MAX - value) ||
                (value < 0 && even_sum < LLONG_MIN - value)) {
                return -1;
            }
            even_sum += value;
        } else {
            if ((value > 0 && odd_sum > LLONG_MAX - value) ||
                (value < 0 && odd_sum < LLONG_MIN - value)) {
                return -1;
            }
            odd_sum += value;
        }

        head = head->next;
        ++index;
    }

    *first_sum = even_sum;
    *second_sum = odd_sum;
    return 0;
}

static void free_chain(Tuple *head)
{
    while (head != NULL) {
        Tuple *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    Tuple *head = NULL;
    Tuple *tail = NULL;
    size_t count;
    long long even_sum;
    long long odd_sum;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        Tuple *node = malloc(sizeof(*node));

        if (node == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free_chain(head);
            return EXIT_FAILURE;
        }

        if (scanf("%lld %lld", &node->first, &node->second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(node);
            free_chain(head);
            return EXIT_FAILURE;
        }

        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    if (sum_alternate_chains(head, &even_sum, &odd_sum) != 0) {
        fputs("Arithmetic overflow or invalid argument\n", stderr);
        free_chain(head);
        return EXIT_FAILURE;
    }

    printf("%lld %lld\n", even_sum, odd_sum);
    free_chain(head);
    return EXIT_SUCCESS;
}