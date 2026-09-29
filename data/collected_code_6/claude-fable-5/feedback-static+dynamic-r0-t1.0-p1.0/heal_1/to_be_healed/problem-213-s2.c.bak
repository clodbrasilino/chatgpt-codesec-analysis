#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Manjeet Singh', 'Nikhil Meherwal', 'Akshat Garg'], got <no output>
  *  test case 1 failed: expected ['Shaik Dawood', 'Ayesha Begum', 'Sanya Singh'], got <no output>
  *  test case 2 failed: expected ['HarpreetKour', 'Priyanka Agarwal', 'MuskanSethi'], got <no output>
  */

static char *concat_strings(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    char *result;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    len_a = strlen(a);
    len_b = strlen(b);

    result = malloc(len_a + len_b + 1U);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b + 1U);

    return result;
}

static int concat_tuples(const StringTuple *t1, const StringTuple *t2, StringTuple *out)
{
    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    out->first = concat_strings(t1->first, t2->first);
    if (out->first == NULL) {
        return -1;
    }

    out->second = concat_strings(t1->second, t2->second);
    if (out->second == NULL) {
        free(out->first);
        out->first = NULL;
        return -1;
    }

    return 0;
}

static void free_tuple(StringTuple *t)
{
    if (t != NULL) {
        free(t->first);
        free(t->second);
        t->first = NULL;
        t->second = NULL;
    }
}

int main(void)
{
    StringTuple t1;
    StringTuple t2;
    StringTuple result;

    t1.first = "Hello, ";
    t1.second = "Good ";
    t2.first = "World";
    t2.second = "Morning";

    result.first = NULL;
    result.second = NULL;

    if (concat_tuples(&t1, &t2, &result) != 0) {
        fprintf(stderr, "Tuple concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("(%s, %s)\n", result.first, result.second) < 0) {
        free_tuple(&result);
        return EXIT_FAILURE;
    }

    free_tuple(&result);

    return EXIT_SUCCESS;
}