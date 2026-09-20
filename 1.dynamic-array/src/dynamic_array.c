#include "dynamic_array.h"
#include <stdlib.h>

bool da_init(DynamicArray *a, size_t cap,
             size_t (*alloc_strategy)(int current_cap)) {
  if (cap <= 0)
    return false;
  a->data = calloc(cap, sizeof(*a->data));

  if (a->data == NULL)
    return false;

  a->size = 0;
  a->capacity = cap;
  a->alloc_strategy = alloc_strategy;

  return true;
}

void da_destroy(DynamicArray *a) {
  free(a->data);
  a->data = NULL;
  a->size = a->capacity = 0;
}

bool da_push(DynamicArray *a, int x) {
  // Extend capacity if full
  if (a->size == a->capacity) {
    int new_cap =
        a->alloc_strategy ? a->alloc_strategy(a->capacity) : a->capacity * 2;
    da_reserve(a, new_cap);
  }

  a->data[a->size] = x;
  ++a->size;

  return true;
}

bool da_pop(DynamicArray *a, int *out) {
  if (a->size == 0)
    return false;
  if (out)
    *out = a->data[a->size - 1];
  --a->size;
  return true;
}

bool da_get(const DynamicArray *a, size_t i, int *out) {
  if (i >= a->size || i < 0)
    return false;
  if (out)
    *out = a->data[i];
  return true;
}

bool da_set(DynamicArray *a, size_t i, int x) {
  if (i >= a->size)
    return false;
  a->data[i] = x;
  return true;
}

bool da_insert(DynamicArray *a, size_t i, int x) {
  // Extend capacity if full
  if (a->size == a->capacity) {
    int new_cap =
        a->alloc_strategy ? a->alloc_strategy(a->capacity) : a->capacity * 2;
    da_reserve(a, new_cap);
  }

  if (i > a->size) {
    return false;
  }

  size_t j = a->size;
  while (j != i) {
    a->data[j] = a->data[j - 1];
    --j;
  }
  a->data[j] = x;
  ++a->size;

  return true;
}

bool da_erase(DynamicArray *a, size_t i) {
  if (a->size == 0 || i >= a->size)
    return false;

  for (size_t j = i; j < a->size - 1; ++j) {
    a->data[j] = a->data[j + 1];
  }
  --a->size;

  return true;
}

bool da_reserve(DynamicArray *a, size_t cap) {
  int *tmp = realloc(a->data, cap * sizeof(*a->data));
  if (tmp == NULL)
    return false;

  a->data = tmp;
  a->capacity = cap;
  a->copies += a->size;

  return true;
}

bool da_shrink_to_fit(DynamicArray *a) {
  int new_cap = a->size > 0 ? a->size : 1;
  int *tmp = realloc(a->data, new_cap * sizeof(*a->data));
  if (tmp == NULL)
    return false;
  a->data = tmp;
  a->capacity = new_cap;
  return true;
}
