#include "Stack.hh"
#include <cassert>

int main() {
  Stack s;
  st_push(&s, 10);
  st_push(&s, 20);
  int out;
  assert(st_pop(&s, &out));
  assert(out == 20);
}
