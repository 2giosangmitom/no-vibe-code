#include "Deque.h"

#include <assert.h>
#include <stdio.h>

static void test_init(void) {
  Deque dq;
  dq_init(&dq, 4);

  assert(dq.data != NULL);
  assert(dq.capacity == 4);
  assert(dq.size == 0);
  assert(dq.head == 0);

  dq_cleanup(&dq);
}

static void test_push_and_peek(void) {
  Deque dq;
  dq_init(&dq, 4);

  dq_push_back(&dq, 10);
  dq_push_back(&dq, 20);
  dq_push_back(&dq, 30);

  int x;
  assert(dq_front(&dq, &x) && x == 10);
  assert(dq_back(&dq, &x) && x == 30);
  assert(dq.size == 3);

  dq_push_front(&dq, 5);
  assert(dq_front(&dq, &x) && x == 5);
  assert(dq_back(&dq, &x) && x == 30);
  assert(dq.size == 4);

  dq_cleanup(&dq);
}

static void test_pop(void) {
  Deque dq;
  dq_init(&dq, 4);

  dq_push_back(&dq, 10);
  dq_push_back(&dq, 20);
  dq_push_back(&dq, 30);

  int x;
  assert(dq_pop_front(&dq));
  assert(dq_front(&dq, &x) && x == 20);

  assert(dq_pop_back(&dq));
  assert(dq_back(&dq, &x) && x == 20);
  assert(dq.size == 1);

  dq_cleanup(&dq);
}

static void test_empty(void) {
  Deque dq;
  dq_init(&dq, 4);

  int x;
  assert(!dq_front(&dq, &x));
  assert(!dq_back(&dq, &x));
  assert(!dq_pop_front(&dq));
  assert(!dq_pop_back(&dq));

  dq_cleanup(&dq);
}

static void test_growth(void) {
  Deque dq;
  dq_init(&dq, 2);

  for (int i = 0; i < 10; ++i)
    dq_push_back(&dq, i);

  assert(dq.size == 10);
  assert(dq.capacity >= 10);

  for (int i = 0; i < 10; ++i) {
    int x;
    assert(dq_front(&dq, &x) && x == i);
    assert(dq_pop_front(&dq));
  }

  assert(dq.size == 0);

  dq_cleanup(&dq);
}

static void test_reserve(void) {
  Deque dq;
  dq_init(&dq, 4);

  dq_push_back(&dq, 1);
  dq_push_back(&dq, 2);
  dq_push_back(&dq, 3);
  assert(dq_pop_front(&dq)); // bỏ 1
  dq_push_back(&dq, 4);      // còn 2, 3, 4

  assert(dq_reserve(&dq, 8));
  assert(dq.capacity == 8);
  assert(dq.size == 3);
  assert(dq.head == 0);

  int expected[] = {2, 3, 4};
  for (int i = 0; i < 3; ++i) {
    int x;
    assert(dq_front(&dq, &x) && x == expected[i]);
    assert(dq_pop_front(&dq));
  }

  dq_cleanup(&dq);
}

int main() {
  test_init();
  test_push_and_peek();
  test_pop();
  test_empty();
  test_growth();
  test_reserve();

  printf("All Deque tests passed!\n");
  return 0;
}
