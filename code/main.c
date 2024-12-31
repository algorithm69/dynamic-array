#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *data;
    size_t count;
    size_t capacity;
} Dyn_arr;

Dyn_arr *create_dynamic_array(size_t capacity) {
    Dyn_arr *arr = malloc(sizeof(Dyn_arr));
    arr->data = malloc(sizeof(int) * capacity);
    arr->capacity = capacity;
    arr->count = 0;
    return arr;
}

#define DA_INIT_CAPACITY 5

#define da_init(da)                                                                 \
    do {                                                                            \
        (da).capacity = DA_INIT_CAPACITY;                                           \
        (da).data = malloc((da).capacity * sizeof((da).data[0]));                   \
        if (!(da).data) {                                                           \
            fprintf(stderr, "da_init: Cannot allocate memory for dynamic array.");  \
            exit(1);                                                                \
        }                                                                           \
        (da).count = 0;                                                             \
    }                                                                               \
    while (0)

#define da_append(da, elt)                                                          \
    do {                                                                            \
        if ((da).count == (da).capacity) {                                          \
            size_t new_capacity = (da).capacity * 2 ;                               \
            void *ptr = realloc((da).data, new_capacity * sizeof((da).data[0]));    \
            if (!ptr) {                                                             \
                fprintf(stderr, "Cannot allocate memory for dynamic array.");       \
                exit(1);                                                            \
            }                                                                       \
            (da).data = ptr;                                                        \
            (da).capacity = new_capacity;                                           \
        }                                                                           \
        (da).data[(da).count] = elt;                                                \
        (da).count++;                                                               \
    }                                                                               \
    while (0)

struct dyn_array {
    int *data;
    size_t count;
    size_t capacity;
};

int main(void) {
    struct dyn_array da;
    da_init(da);

    //  append an element
    da_append(da, 34);
    printf("%llu/%llu\n", da.count, da.capacity);
    da_append(da, 39);
    printf("%llu/%llu\n", da.count, da.capacity);
    da_append(da, 49);
    printf("%llu/%llu\n", da.count, da.capacity);

    for (int i = 0; i < 3; i++) {
        printf("%d ", da.data[i]);
    }
    printf("\n");


    return 0;
}
