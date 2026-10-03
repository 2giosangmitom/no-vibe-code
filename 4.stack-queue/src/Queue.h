#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *buf;
  size_t count, capacity, head;
} Queue;

void q_init(Queue *q, size_t cap);

bool q_reserve(Queue *q, size_t cap);

bool q_enqueue(Queue *q, int x);

bool q_dequeue(Queue *q, int *out);

bool q_front(const Queue *q, int *out);

void q_clean(Queue *q);

#endif // QUEUE_H
