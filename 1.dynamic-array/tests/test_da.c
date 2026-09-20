#include <assert.h>
#include <dynamic_array.h>
#include <stdio.h>

int main() {
  DynamicArray a;

  da_init(&a, 2, NULL);
  da_push(&a, 1);
  da_push(&a, 2);
  da_push(&a, 3);
  assert(a.size == 3);
  assert(a.capacity == 4);

  int out = 0;
  da_get(&a, 1, &out);
  assert(out == 2);

  da_insert(&a, 1, 9);
  da_get(&a, 1, &out);
  assert(out == 9);
  da_insert(&a, 4, 7);
  da_get(&a, 4, &out);
  assert(out == 7);

  da_erase(&a, 1);
  assert(a.size == 4);
  int expected[] = {1, 2, 3, 7};
  for (size_t i = 0; i < a.size; ++i) {
    da_get(&a, i, &out);
    assert(out == expected[i]);
  }

  da_pop(&a, &out);
  assert(out == 7);
  assert(a.size == 3);

  assert(!da_get(&a, 5, &out));
  assert(!da_set(&a, 5, 0));
  assert(!da_erase(&a, 5));
  assert(a.size == 3);

  int before[] = {1, 2, 3};
  for (size_t i = 0; i < a.size; ++i) {
    assert(da_get(&a, i, &out));
    assert(out == before[i]);
  }

  assert(!da_insert(&a, 9, 0));
  assert(a.size == 3);
  for (size_t i = 0; i < a.size; ++i) {
    assert(da_get(&a, i, &out));
    assert(out == before[i]);
  }

  assert(da_pop(&a, &out));
  assert(out == 3);
  assert(a.size == 2);

  assert(da_pop(&a, &out));
  assert(out == 2);
  assert(a.size == 1);

  assert(da_pop(&a, &out));
  assert(out == 1);
  assert(a.size == 0);

  assert(!da_pop(&a, &out));
  assert(a.size == 0);

  assert(da_reserve(&a, 100));
  assert(a.capacity == 100);

  assert(da_shrink_to_fit(&a));
  assert(a.capacity == 1);

  da_destroy(&a);

  printf("All tests passed successfully!");
}
