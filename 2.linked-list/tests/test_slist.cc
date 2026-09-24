#include "slist.hh"
#include <cassert>
#include <iostream>

void print_sl(SList *l) {
  for (Node *curr = l->head; curr != nullptr; curr = curr->next) {
    std::cout << curr->val << " ";
  }
  std::cout << std::endl;
  std::cout << "head: " << l->head->val << std::endl;
  std::cout << "tail: " << l->tail->val << std::endl;
}

int main() {
  SList l = SList();
  sl_init(&l);

  sl_push_front(&l, 3);
  sl_push_front(&l, 4);
  sl_push_front(&l, 5);
  print_sl(&l);

  sl_push_back(&l, 6);
  print_sl(&l);

  int out;
  sl_pop_front(&l, &out);
  std::cout << out << std::endl;
  print_sl(&l);

  sl_insert_after(&l, l.head->next, 10);
  sl_insert_after(&l, l.tail, 11);
  print_sl(&l);

  sl_remove(&l, 11);
  sl_remove(&l, 4);
  print_sl(&l);

  Node *first_node = sl_find(&l, l.head->val);
  assert(first_node == l.head);

  sl_reverse(&l);
  print_sl(&l);

  sl_get(&l, 1, &out);
  assert(out == 6);

  sl_clear(&l);
}
