#ifndef STACK_HH
#define STACK_HH

#include <vector>

struct Stack {
  std::vector<int> data;
};

bool st_push(Stack *s, int x);

bool st_pop(Stack *s, int *out);

bool st_peek(const Stack *s, int *out);

bool st_empty(const Stack *s);

size_t st_size(Stack *s);

#endif // STACK_HH
