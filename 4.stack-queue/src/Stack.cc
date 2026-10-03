#include "Stack.hh"

bool st_push(Stack *s, int x) {
  s->data.push_back(x);
  return true;
}

bool st_pop(Stack *s, int *out) {
  if (!st_peek(s, out))
    return false;
  s->data.pop_back();
  return true;
}

bool st_peek(const Stack *s, int *out) {
  if (s->data.empty())
    return false;
  *out = s->data.back();
  return true;
}

bool st_empty(const Stack *s) { return s->data.empty(); }

size_t st_size(Stack *s) { return s->data.size(); }
