#include "dynamic_array.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

size_t x2(int current_cap) { return current_cap * 2; }

size_t x1dot5(int current_cap) { return (size_t)ceil(current_cap * 1.5); }

size_t add1(int current_cap) { return current_cap + 1; }

int main() {
  DynamicArray a_x2;
  da_init(&a_x2, 1, &x2);

  DynamicArray a_x1dot5;
  da_init(&a_x1dot5, 1, &x1dot5);

  DynamicArray a_add1;
  da_init(&a_add1, 1, &add1);

  size_t prev_cap = a_x2.capacity;
  for (int i = 1; i <= 10; ++i) {
    da_push(&a_x2, i);
    if (a_x2.capacity != prev_cap) {
      printf("a_x2:new_cap = %zu\n", a_x2.capacity);
      prev_cap = a_x2.capacity;
    }
  }
  // Restore old state
  for (int i = 1; i <= 10; ++i) {
    da_pop(&a_x2, NULL);
  }
  da_shrink_to_fit(&a_x2);

  for (int i = 1; i <= 1e5; ++i) {
    da_push(&a_x2, i);
    da_push(&a_x1dot5, i);
    da_push(&a_add1, i);
  }
  printf("%-10s %-10s %-15s %s\n", "strategy", "n", "copies", "copies/n");
  printf("%-10s %-10zu %-15zu %.6f\n", "x2", a_x2.size, a_x2.copies,
         (double)a_x2.copies / a_x2.size);
  printf("%-10s %-10zu %-15zu %.6f\n", "x1.5", a_x1dot5.size, a_x1dot5.copies,
         (double)a_x1dot5.copies / a_x1dot5.size);
  printf("%-10s %-10zu %-15zu %.6f\n", "+1", a_add1.size, a_add1.copies,
         (double)a_add1.copies / a_add1.size);

  da_destroy(&a_x2);
  da_destroy(&a_x1dot5);
  da_destroy(&a_add1);
}
