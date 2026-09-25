#include "dlist.hh"
#include <cassert>
#include <iostream>

void print_dl(DList *l) {
  for (DNode *curr = l->head; curr != nullptr; curr = curr->next) {
    std::cout << curr->val << " ";
  }
  std::cout << std::endl;
  std::cout << "head: " << l->head->val << std::endl;
  std::cout << "tail: " << l->tail->val << std::endl;
}

int main() {
  DList l;
  dl_init(&l);

  dl_push_front(&l, 10);
  dl_push_front(&l, 9);
  print_dl(&l);

  dl_push_back(&l, 11);
  dl_push_back(&l, 12);
  print_dl(&l);

  int out;
  dl_pop_front(&l, &out);
  assert(out == 9);
  print_dl(&l);

  dl_insert_after(&l, l.head->next, 15);
  dl_insert_after(&l, l.tail, 20);
  print_dl(&l);

  dl_remove(&l, 20);
  dl_remove(&l, 10);
  dl_remove(&l, 15);
  print_dl(&l);

  DNode *n12 = dl_find(&l, 12);
  assert(n12 == l.head->next);

  dl_get(&l, 2, &out);
  assert(12 == out);

  dl_push_back(&l, 40);
  print_dl(&l);
  dl_remove_node(&l, l.head->next);
  print_dl(&l);

  dl_clear(&l);
}
