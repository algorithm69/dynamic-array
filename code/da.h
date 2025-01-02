//
// Created by duval on 2025-01-02.
//

#ifndef DA_H
#define DA_H

#include <string.h>

#define DA_ASSERT(cond, msg)                        \
    do {                                            \
        if (!(cond)) {                              \
            fprintf(stderr, "ERROR: %s\n", msg);    \
            exit(1);                                \
        }                                           \
    } while (0)

#define DA_INIT_CAP 1

// A dynamic array must have these 3 fields :
//  - items
//  - count
//  - capacity

#define da_clear(da) (da)->count=0

#define da_free(da)             \
    do {                        \
        free((da)->items);      \
        (da)->count = 0;        \
    } while(0)

#define da_reset(da)                                                    \
    do {                                                                \
        da_free(da);                                                    \
        (da)->capacity = DA_INIT_CAP;                                   \
        (da)->items = malloc((da).capacity * sizeof((da).data[0]));     \
        DA_ASSERT((da)->items, "da_init: Cannot allocate memory.");     \
        (da)->count = 0;                                                \
    }                                                                   \
    while (0)

#define da_append(da, elt)                                                                  \
    do {                                                                                    \
        if ((da)->count == (da)->capacity) {                                                \
            (da)->capacity = (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity * 2 ;       \
            (da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items));      \
            DA_ASSERT((da)->items, "da_append: Cannot allocate memory.");                   \
        }                                                                                   \
        (da)->items[(da)->count++] = elt;                                                   \
    } while (0)

#define da_append_many(da, ptr_new_items, new_items_count)                                          \
    do {                                                                                            \
        if ((da)->capacity == 0) (da)->capacity = DA_INIT_CAP;                                      \
        while ((da) -> count + new_items_count > (da) -> capacity ) {                               \
            (da)->capacity *= 2;                                                                    \
        }                                                                                           \
        (da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items));                  \
        DA_ASSERT((da)->items, "da_append: Cannot allocate memory.");                               \
        memcpy((da)->items + (da)->count, (ptr_new_items), (new_items_count)*sizeof(*(da)->items)); \
        (da)->count += new_items_count;                                                             \
    } while (0)

#define DA_ITEM_TYPE(da) typeof((da)->items[0])
#define DA_SIZE_OF_ITEM(da) sizeof((da)->items[0])

#define da_append_args(da, ...)                                                                     \
    do {                                                                                            \
        printf("size: %u\n", sizeof((DA_ITEM_TYPE(da)[]){__VA_ARGS__})/DA_SIZE_OF_ITEM(da));        \
        da_append_many( da,                                                                         \
                        (DA_ITEM_TYPE(da)[]){__VA_ARGS__},                                          \
                        sizeof((DA_ITEM_TYPE(da)[]){__VA_ARGS__})/DA_SIZE_OF_ITEM(da));             \
    } while(0)

#define da_foreach(elt, da) for (typeof((da)->items) elt = (da)->items; elt < (da)->items + (da)->count; elt++)

#endif //DA_H
