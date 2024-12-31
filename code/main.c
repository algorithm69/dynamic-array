#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DA_INIT_CAPACITY 1

#define da_init(da)                                                                         \
    do {                                                                                    \
        (da).capacity = DA_INIT_CAPACITY;                                                   \
        (da).data = malloc((da).capacity * sizeof((da).data[0]));                           \
        if (!(da).data) {                                                                   \
            fprintf(stderr, "da_init: Cannot allocate memory for dynamic array.");          \
            exit(1);                                                                        \
        }                                                                                   \
        (da).count = 0;                                                                     \
    }                                                                                       \
    while (0)

#define da_append(da, elt)                                                                  \
    do {                                                                                    \
        if ((da).count == (da).capacity) {                                                  \
            size_t new_capacity = (da).capacity * 2 ;                                       \
            void *ptr = realloc((da).data, new_capacity * sizeof((da).data[0]));            \
            if (!ptr) {                                                                     \
                fprintf(stderr, "da_append: Cannot allocate memory for dynamic array.");    \
                exit(1);                                                                    \
            }                                                                               \
            (da).data = ptr;                                                                \
            (da).capacity = new_capacity;                                                   \
        }                                                                                   \
        (da).data[(da).count] = elt;                                                        \
        (da).count++;                                                                       \
    }                                                                                       \
    while (0)

#define da_foreach(type, elt, da, body) \
    for(int i=0; i<(da).count; i++) {   \
        type elt=(da).data[i];          \
        body                            \
    }

//  test
struct dyn_array {
    int *data;
    size_t count;
    size_t capacity;
};

int main(void) {
    srand(time(NULL));

    struct dyn_array da;
    da_init(da);

    //  append an element
    for (int i = 0; i < 10; i++) {
        da_append(da, rand() % 100);
        printf("%llu/%llu\n", da.count, da.capacity);
    }

    da_foreach(int, n, da, {
               printf("%d ", n);
               });
    printf("\n");

    for (int i = 0; i < da.count; i++) {
        printf("%d ", da.data[i]);
    }
    printf("\n");

    return 0;
}
