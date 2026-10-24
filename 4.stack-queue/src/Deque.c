#include "Deque.h"
#include <stdlib.h>

void dq_init(Deque *dq, size_t capacity) {
  dq->data = calloc(capacity, sizeof(*dq->data));
  dq->size = 0;
  dq->capacity = capacity;
  dq->head = 0;
}

void dq_push_front(Deque *dq, int x) {
  if (dq->capacity == dq->size)
    if (!dq_reserve(dq, dq->capacity * 2))
      return;

  dq->data[(dq->head - 1) % dq->capacity] = x;
  ++dq->size;
  dq->head = (dq->head - 1) % dq->capacity;
}

bool dq_reserve(Deque *dq, size_t new_capacity) {
  if (dq->capacity > new_capacity)
    return false;

  int *tmp = calloc(new_capacity, sizeof(*dq->data));
  if (!tmp)
    return false;

  for (size_t i = 0; i < dq->size; ++i) {
    tmp[i] = dq->data[(i + dq->head) % dq->capacity];
  }
  dq->capacity = new_capacity;
  dq->head = 0;
  free(dq->data);
  dq->data = tmp;

  return true;
}

void dq_push_back(Deque *dq, int x) {
  if (dq->capacity == dq->size)
    if (!dq_reserve(dq, dq->capacity * 2))
      return;

  dq->data[(dq->head + dq->size) % dq->capacity] = x;
  ++dq->size;
}

bool dq_pop_front(Deque *dq) {
  if (dq->size == 0)
    return false;

  dq->head = (dq->head + 1) % dq->capacity;
  --dq->size;

  return true;
}

bool dq_pop_back(Deque *dq) {
  if (dq->size == 0)
    return false;

  --dq->size;

  return true;
}

bool dq_front(Deque *dq, int *x) {
  if (dq->size == 0)
    return false;

  *x = dq->data[dq->head];

  return true;
}

bool dq_back(Deque *dq, int *x) {
  if (dq->size == 0)
    return false;

  *x = dq->data[(dq->head + dq->size - 1) % dq->capacity];

  return true;
}

void dq_cleanup(Deque *dq) {
  free(dq->data);
  dq->data = NULL;
}
