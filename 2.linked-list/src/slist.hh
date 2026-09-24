#ifndef SLIST_HH
#define SLIST_HH

#include <cstddef>

struct Node {
  int val;
  struct Node *next;
};

struct SList {
  Node *head;
  Node *tail;
  size_t size;
};

void sl_init(SList *l);

bool sl_push_front(SList *l, int x);

bool sl_push_back(SList *l, int x);

bool sl_pop_front(SList *l, int *out);

bool sl_insert_after(SList *l, Node *n, int x);

bool sl_remove(SList *l, int x);

Node *sl_find(const SList *l, int x);

bool sl_get(const SList *l, size_t k, int *out);

void sl_reverse(SList *l);

void sl_clear(SList *l);

#endif // SLIST_HH
