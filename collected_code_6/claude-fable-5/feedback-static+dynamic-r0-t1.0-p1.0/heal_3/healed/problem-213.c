if (len_b > SIZE_MAX - 1U || len_a > SIZE_MAX - len_b - 1U) {
    return NULL;
}