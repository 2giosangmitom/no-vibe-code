#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *data;
  size_t size;
  size_t capacity;

  // Count total number of elements copied
  size_t copies;
  size_t (*alloc_strategy)(int current_cap);
} DynamicArray;

bool da_init(DynamicArray *a, size_t cap,
             size_t (*alloc_strategy)(int current_cap));

void da_destroy(DynamicArray *a);

bool da_push(DynamicArray *a, int x);

bool da_pop(DynamicArray *a, int *out);

bool da_get(const DynamicArray *a, size_t i, int *out);

bool da_set(DynamicArray *a, size_t i, int x);

bool da_insert(DynamicArray *a, size_t i, int x);

bool da_erase(DynamicArray *a, size_t i);

bool da_reserve(DynamicArray *a, size_t cap);

bool da_shrink_to_fit(DynamicArray *a);

#endif // DYNAMIC_ARRAY_H
