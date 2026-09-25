#ifndef DLIST_HH
#define DLIST_HH

#include <cstddef>

struct DNode {
  int val;
  struct DNode *next;
  struct DNode *prev;
};

struct DList {
  DNode *head;
  DNode *tail;
  size_t size;
};

void dl_init(DList *l);

bool dl_push_front(DList *l, int x);

bool dl_push_back(DList *l, int x);

bool dl_pop_front(DList *l, int *out);

bool dl_insert_after(DList *l, DNode *n, int x);

bool dl_remove(DList *l, int x);

DNode *dl_find(const DList *l, int x);

bool dl_get(const DList *l, size_t k, int *out);

void dl_clear(DList *l);

void dl_remove_node(DList *l, DNode *n);

#endif // DLIST_HH
