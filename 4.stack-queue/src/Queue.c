#include "Queue.h"
#include <stdbool.h>
#include <stdlib.h>

void q_init(Queue *q, size_t cap) {
  q->count = 0;
  q->head = 0;
  q->buf = calloc(cap, sizeof(*q->buf));
  q->capacity = cap;
}

bool q_reserve(Queue *q, size_t cap) {
  if (cap < q->capacity)
    return true;

  int *tmp = calloc(cap, sizeof(*q->buf));
  if (!tmp)
    return false;

  for (size_t i = 0; i < q->count; ++i) {
    tmp[i] = q->buf[(q->head + i) % q->capacity];
  }
  free(q->buf);
  q->buf = tmp;
  q->capacity = cap;
  q->head = 0;

  return true;
}

bool q_enqueue(Queue *q, int x) {
  if (q->count == q->capacity) {
    if (!q_reserve(q, q->capacity * 2))
      return false;
  }

  q->buf[(q->head + q->count) % q->capacity] = x;
  ++q->count;

  return true;
}

bool q_dequeue(Queue *q, int *out) {
  if (q->count == 0)
    return false;

  *out = q->buf[q->head];
  q->head = (q->head + 1) % q->capacity;
  --q->count;

  return true;
}

bool q_front(const Queue *q, int *out) {
  if (q->count == 0)
    return false;

  *out = q->buf[q->head];

  return true;
}

void q_clean(Queue *q) {
  free(q->buf);
  q->count = q->capacity = q->head = 0;
}
