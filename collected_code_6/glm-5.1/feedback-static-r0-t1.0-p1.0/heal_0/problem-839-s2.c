#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    return strcmp(ta->first, tb->first);
}

int main(void) {
    char str1[] = "banana";
    char str2[] = "apple";
    char str3[] = "cherry";
    char str4[] = "yellow";
    char str5[] = "red";
    char str6[] = "green";

    Tuple tuples[] = {
        {str1, str4},
        {str2, str5},
        {str3, str6}
    };

    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    qsort(tuples, num_tuples, sizeof(Tuple), compare_tuples);

    for (size_t i = 0; i < num_tuples; i++) {
        printf("(%s, %s)\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}