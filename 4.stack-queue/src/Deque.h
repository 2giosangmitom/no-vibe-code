#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *data;
  size_t head;
  size_t capacity;
  size_t size;
} Deque;

void dq_init(Deque *dq, size_t cap);

void dq_push_front(Deque *dq, int x);

void dq_push_back(Deque *dq, int x);

bool dq_pop_front(Deque *dq);

bool dq_pop_back(Deque *dq);

bool dq_front(Deque *dq, int *x);

bool dq_back(Deque *dq, int *x);

bool dq_reserve(Deque *dq, size_t new_capacity);

void dq_cleanup(Deque *dq);

#endif // DEQUE_H