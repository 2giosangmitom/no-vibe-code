#include "slist.hh"

void sl_init(SList *l) {
  l->size = 0;
  l->head = l->tail = nullptr;
}

bool sl_push_front(SList *l, int x) {
  Node *new_node = new Node{x, nullptr};
  if (!new_node)
    return false;

  if (l->size == 0) {
    l->head = l->tail = new_node;
  } else {
    new_node->next = l->head;
    l->head = new_node;
  }
  ++l->size;

  return true;
}

bool sl_push_back(SList *l, int x) {
  Node *new_node = new Node{x, nullptr};
  if (!new_node)
    return false;

  if (l->size == 0) {
    l->head = l->tail = new_node;
  } else {
    l->tail->next = new_node;
    l->tail = new_node;
  }
  ++l->size;

  return true;
}

bool sl_pop_front(SList *l, int *out) {
  if (l->size == 0)
    return false;

  Node *new_head = l->head->next;
  *out = l->head->val;
  delete l->head;
  l->head = new_head;
  --l->size;

  if (l->size == 0) {
    l->tail = nullptr; // null
  }

  return true;
}

bool sl_insert_after(SList *l, Node *n, int x) {
  if (n == nullptr)
    return false;

  Node *new_node = new Node{x, nullptr};
  new_node->next = n->next;
  n->next = new_node;

  if (l->tail == n)
    l->tail = new_node;

  return true;
}

bool sl_remove(SList *l, int x) {
  Node dummy_head = Node{0, l->head};
  Node *current = &dummy_head;

  while (current->next && current->next->val != x) {
    current = current->next;
  }

  if (current->next) {
    Node *next = current->next->next;
    if (current->next == l->tail) {
      l->tail = current;
    }
    delete current->next;
    current->next = next;
  }

  l->head = dummy_head.next;

  return true;
}

Node *sl_find(const SList *l, int x) {
  Node *current = l->head;

  while (current && current->val != x)
    current = current->next;

  return current;
}

bool sl_get(const SList *l, size_t k, int *out) {
  Node *current = l->head;

  for (size_t i = 1; current && i < k; ++i) {
    current = current->next;
  }
  if (!current)
    return false;

  *out = current->val;

  return true;
}

void sl_reverse(SList *l) {
  Node *prev = nullptr, *current = l->head;
  l->tail = current;

  while (current != nullptr) {
    Node *tmp = current->next;
    current->next = prev;
    prev = current;
    current = tmp;
  }

  l->head = prev;
}

void sl_clear(SList *l) {
  Node *curr = l->head;

  while (curr) {
    Node *next = curr->next;
    delete curr;
    curr = next;
  }

  l->head = nullptr;
  l->tail = nullptr;
}
