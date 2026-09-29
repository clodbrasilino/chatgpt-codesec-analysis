#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    int value;
    int *partners;
    size_t partner_count;
} ElementPartners;

static void free_element_partners(ElementPartners *elements, size_t count)
{
    if (elements == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(elements[i].partners);
    }

    free(elements);
}

static int add_partner(ElementPartners *element, int partner)
{
    int *new_partners;

    if (element == NULL || element->partner_count == SIZE_MAX / sizeof(*new_partners)) {
        return -1;
    }

    new_partners = realloc(
        element->partners,
        (element->partner_count + 1) * sizeof(*new_partners)
    );

    if (new_partners == NULL) {
        return -1;
    }

    element->partners = new_partners;
    element->partners[element->partner_count] = partner;
    ++element->partner_count;

    return 0;
}

static size_t find_element(
    const ElementPartners *elements,
    size_t count,
    int value
)
{
    for (size_t i = 0; i < count; ++i) {
        if (elements[i].value == value) {
            return i;
        }
    }

    return count;
}

static int assign_pair_elements(
    const Pair *pairs,
    size_t pair_count,
    ElementPartners **result,
    size_t *result_count
)
{
    ElementPartners *elements;
    size_t capacity;
    size_t count = 0;

    if (result == NULL || result_count == NULL ||
        (pair_count != 0 && pairs == NULL) ||
        pair_count > SIZE_MAX / 2 ||
        pair_count * 2 > SIZE_MAX / sizeof(*elements)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (pair_count == 0) {
        return 0;
    }

    capacity = pair_count * 2;
    elements = calloc(capacity, sizeof(*elements));
    if (elements == NULL) {
        return -1;
    }

    for (size_t i = 0; i < pair_count; ++i) {
        size_t first_index = find_element(elements, count, pairs[i].first);
        size_t second_index;

        if (first_index == count) {
            elements[count].value = pairs[i].first;
            first_index = count++;
        }

        second_index = find_element(elements, count, pairs[i].second);
        if (second_index == count) {
            elements[count].value = pairs[i].second;
            second_index = count++;
        }

        if (add_partner(&elements[first_index], pairs[i].second) != 0 ||
            add_partner(&elements[second_index], pairs[i].first) != 0) {
            free_element_partners(elements, count);
            return -1;
        }
    }

    *result = elements;
    *result_count = count;
    return 0;
}

int main(void)
{
    const Pair pairs[] = {
        {1, 2},
        {3, 4},
        {1, 5},
        {2, 6},
        {3, 1}
    };
    ElementPartners *elements = NULL;
    size_t element_count = 0;
    size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);

    if (assign_pair_elements(
            pairs,
            pair_count,
            &elements,
            &element_count
        ) != 0) {
        fputs("Failed to assign pair elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        printf("%d:", elements[i].value);

        for (size_t j = 0; j < elements[i].partner_count; ++j) {
            printf(" %d", elements[i].partners[j]);
        }

        putchar('\n');
    }

    free_element_partners(elements, element_count);
    return EXIT_SUCCESS;
}