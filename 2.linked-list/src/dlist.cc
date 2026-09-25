#include "dlist.hh"

void dl_init(DList *l) {
  l->head = l->tail = nullptr;
  l->size = 0;
}

bool dl_push_front(DList *l, int x) {
  DNode *new_node = new DNode{x, nullptr, nullptr};
  if (!new_node)
    return false;

  if (l->size == 0) {
    l->head = l->tail = new_node;
    ++l->size;
    return true;
  }
  ++l->size;

  new_node->next = l->head;
  l->head->prev = new_node;
  l->head = new_node;

  return true;
}

bool dl_push_back(DList *l, int x) {
  DNode *new_node = new DNode{x, nullptr, nullptr};
  if (l->size == 0) {
    l->tail->next = new_node;
    new_node->prev = l->tail;
    l->tail = new_node;
    ++l->size;
    return true;
  }

  new_node->prev = l->tail;
  l->tail->next = new_node;
  l->tail = new_node;
  ++l->size;

  return true;
}

bool dl_pop_front(DList *l, int *out) {
  if (l->size == 0)
    return false;
  DNode *new_head = l->head->next;

  *out = l->head->val;
  new_head->prev = nullptr;
  delete l->head;
  l->head = new_head;
  --l->size;

  return true;
}

bool dl_insert_after(DList *l, DNode *n, int x) {
  DNode *new_node = new DNode{x, nullptr, nullptr};

  new_node->next = n->next;
  new_node->prev = n;
  n->next = new_node;
  ++l->size;
  if (n == l->tail) {
    l->tail = new_node;
  }

  return true;
}

bool dl_remove(DList *l, int x) {
  DNode *current = l->head;

  for (; current && current->val != x; current = current->next) {
  }

  if (!current)
    return false;

  if (current == l->head) {
    l->head = current->next;
  }
  if (current == l->tail) {
    l->tail = current->prev;
  }
  if (current->prev) {
    current->prev->next = current->next;
  }
  if (current->next) {
    current->next->prev = current->prev;
  }
  delete current;
  --l->size;

  return true;
}

DNode *dl_find(const DList *l, int x) {
  DNode *res = l->head;

  while (res && res->val != x)
    res = res->next;

  return res;
}

bool dl_get(const DList *l, size_t k, int *out) {
  if (k > l->size)
    return false;

  DNode *n = l->head;
  for (size_t i = 1; i < k; i++) {
    n = n->next;
  }

  *out = n->val;

  return true;
}

void dl_remove_node(DList *l, DNode *n) {
  if (n == l->head) {
    l->head = n->next;
  } else if (n == l->tail) {
    l->tail = n->prev;
  } else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }
  delete n;
  --l->size;
}

void dl_clear(DList *l) {
  DNode *current = l->head;
  while (current) {
    DNode *next_node = current->next;
    delete current;
    current = next_node;
  }
  l->head = nullptr;
  l->tail = nullptr;
  l->size = 0;
}
