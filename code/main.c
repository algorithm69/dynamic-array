#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "da.h"

//  test
typedef struct {
    int *items;
    size_t count;
    size_t capacity;
} Numbers;

int main(void) {
    srand(time(NULL)); // NOLINT(*-msc51-cpp)

    Numbers da = {};

    //  append some items one by one
    for (int i = 0; i < 5; i++) {
        da_append(&da, rand() % 100) ; // NOLINT(*-msc50-cpp)
        printf("%llu/%llu\n", da.count, da.capacity);
    }

    //  add many elements at once
    int tab[] = {3, 4, 5, 6};
    da_append_many(&da, tab, 4);
    da_append_many(&da, ((const int[]){1, 2, 3, 4}), 4);
    da_append_args(&da);

    //  for each loop
    da_foreach(elt1, &da) {
        da_foreach(elt2, &da) {
            printf("%d-%d ", *elt1, *elt2);
        }
    }
    printf("\n");

    for (int i = 0; i < da.count; i++) {
        printf("%d ", da.items[i]);
    }
    printf("\n");

    da_free(&da);

    return 0;
}
