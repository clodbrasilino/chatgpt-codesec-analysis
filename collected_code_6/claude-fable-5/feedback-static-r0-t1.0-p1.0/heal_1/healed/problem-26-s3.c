#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool has_all_k_elements(const Tuple *tuples, size_t count, int k)
{
    if (tuples == NULL || count == 0U) {
        return false;
    }

    for (size_t i = 0U; i < count; i++) {
        if ((tuples[i].first != k) || (tuples[i].second != k)) {
            return false;
        }
    }

    return true;
}

static void report_result(const char *name, const Tuple *tuples, size_t count, int k)
{
    if (tuples == NULL) {
        (void)printf("%s is NULL and was handled safely\n", name);
        return;
    }

    if (has_all_k_elements(tuples, count, k)) {
        (void)printf("%s has all elements equal to %d\n", name, k);
    } else {
        (void)printf("%s does not have all elements equal to %d\n", name, k);
    }
}

int main(void)
{
    Tuple list1[] = { {4, 4}, {4, 4}, {4, 4} };
    Tuple list2[] = { {7, 7}, {7, 7}, {7, 8} };
    Tuple list3[] = { {9, 9} };
    const Tuple *list4 = NULL;

    size_t count1 = sizeof(list1) / sizeof(list1[0]);
    size_t count2 = sizeof(list2) / sizeof(list2[0]);
    size_t count3 = sizeof(list3) / sizeof(list3[0]);
    size_t count4 = 0U;

    report_result("List 1", list1, count1, 4);
    report_result("List 2", list2, count2, 7);
    report_result("List 3", list3, count3, 9);
    report_result("List 4", list4, count4, 5);

    return 0;
}