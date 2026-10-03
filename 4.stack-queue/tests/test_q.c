#include "Queue.h"

#include <assert.h>
#include <stdio.h>

static void test_init(void) {
  Queue q;

  q_init(&q, 5);

  assert(q.buf != NULL);
  assert(q.capacity == 5);
  assert(q.count == 0);
  assert(q.head == 0);

  q_clean(&q);
}

static void test_enqueue_front(void) {
  Queue q;
  q_init(&q, 5);

  assert(q_enqueue(&q, 10));
  assert(q.count == 1);

  int value;

  assert(q_front(&q, &value));
  assert(value == 10);

  assert(q_enqueue(&q, 20));
  assert(q_enqueue(&q, 30));
  assert(q.count == 3);

  // front không được xóa phần tử
  assert(q_front(&q, &value));
  assert(value == 10);
  assert(q.count == 3);

  q_clean(&q);
}

static void test_dequeue(void) {
  Queue q;
  q_init(&q, 5);

  assert(q_enqueue(&q, 10));
  assert(q_enqueue(&q, 20));
  assert(q_enqueue(&q, 30));

  int value;

  assert(q_dequeue(&q, &value));
  assert(value == 10);
  assert(q.count == 2);

  assert(q_dequeue(&q, &value));
  assert(value == 20);
  assert(q.count == 1);

  assert(q_dequeue(&q, &value));
  assert(value == 30);
  assert(q.count == 0);

  q_clean(&q);
}

static void test_fifo(void) {
  Queue q;
  q_init(&q, 10);

  for (int i = 0; i < 10; ++i) {
    assert(q_enqueue(&q, i));
  }

  for (int i = 0; i < 10; ++i) {
    int value;

    assert(q_dequeue(&q, &value));
    assert(value == i);
  }

  assert(q.count == 0);

  q_clean(&q);
}

static void test_empty_queue(void) {
  Queue q;
  q_init(&q, 5);

  int value;

  assert(!q_front(&q, &value));
  assert(!q_dequeue(&q, &value));

  assert(q.count == 0);

  q_clean(&q);
}

static void test_wrap_around(void) {
  Queue q;
  q_init(&q, 5);

  /*
      Ban đầu:

      index:  0  1  2  3  4
      value: 10 20 30 40 50
      head = 0
  */

  assert(q_enqueue(&q, 10));
  assert(q_enqueue(&q, 20));
  assert(q_enqueue(&q, 30));
  assert(q_enqueue(&q, 40));
  assert(q_enqueue(&q, 50));

  int value;

  assert(q_dequeue(&q, &value));
  assert(value == 10);

  assert(q_dequeue(&q, &value));
  assert(value == 20);

  /*
      Sau 2 dequeue:

      index:  0  1  2  3  4
                   ^
                 head

      Queue logic:
      30, 40, 50
  */

  assert(q_enqueue(&q, 60));
  assert(q_enqueue(&q, 70));

  /*
      60, 70 phải quay lại đầu mảng vật lý.

      Queue logic:

      30, 40, 50, 60, 70
  */

  assert(q.count == 5);

  int expected[] = {30, 40, 50, 60, 70};

  for (size_t i = 0; i < 5; ++i) {
    assert(q_dequeue(&q, &value));
    assert(value == expected[i]);
  }

  assert(q.count == 0);

  q_clean(&q);
}

static void test_multiple_wrap_around(void) {
  Queue q;
  q_init(&q, 4);

  /*
      Liên tục enqueue/dequeue để head đi qua cuối mảng
      nhiều lần.
  */

  for (int round = 0; round < 100; ++round) {
    for (int i = 0; i < 4; ++i) {
      assert(q_enqueue(&q, round * 4 + i));
    }

    for (int i = 0; i < 4; ++i) {
      int value;

      assert(q_dequeue(&q, &value));
      assert(value == round * 4 + i);
    }

    assert(q.count == 0);
  }

  q_clean(&q);
}

static void test_reserve_empty_queue(void) {
  Queue q;
  q_init(&q, 4);

  assert(q_reserve(&q, 10));

  assert(q.capacity >= 10);
  assert(q.count == 0);

  q_clean(&q);
}

static void test_reserve_with_data(void) {
  Queue q;
  q_init(&q, 4);

  assert(q_enqueue(&q, 10));
  assert(q_enqueue(&q, 20));
  assert(q_enqueue(&q, 30));

  assert(q_reserve(&q, 10));

  assert(q.capacity >= 10);
  assert(q.count == 3);

  int value;

  assert(q_dequeue(&q, &value));
  assert(value == 10);

  assert(q_dequeue(&q, &value));
  assert(value == 20);

  assert(q_dequeue(&q, &value));
  assert(value == 30);

  q_clean(&q);
}

static void test_reserve_after_wrap_around(void) {
  Queue q;
  q_init(&q, 5);

  assert(q_enqueue(&q, 10));
  assert(q_enqueue(&q, 20));
  assert(q_enqueue(&q, 30));
  assert(q_enqueue(&q, 40));
  assert(q_enqueue(&q, 50));

  int value;

  assert(q_dequeue(&q, &value));
  assert(value == 10);

  assert(q_dequeue(&q, &value));
  assert(value == 20);

  assert(q_enqueue(&q, 60));
  assert(q_enqueue(&q, 70));

  /*
      Trước reserve, logic queue là:

      30, 40, 50, 60, 70

      Có thể bố trí vật lý:

      index:  0   1   2   3   4
             60  70  30  40  50
                     ^
                    head
  */

  assert(q.head == 2);
  assert(q.count == 5);

  assert(q_reserve(&q, 10));

  /*
      Sau reserve, theo implementation của bạn:

      index:  0   1   2   3   4   5 ...
             30  40  50  60  70
             ^
            head
  */

  assert(q.capacity >= 10);
  assert(q.count == 5);
  assert(q.head == 0);

  assert(q.buf[0] == 30);
  assert(q.buf[1] == 40);
  assert(q.buf[2] == 50);
  assert(q.buf[3] == 60);
  assert(q.buf[4] == 70);

  int expected[] = {30, 40, 50, 60, 70};

  for (size_t i = 0; i < 5; ++i) {
    assert(q_dequeue(&q, &value));
    assert(value == expected[i]);
  }

  assert(q.count == 0);

  q_clean(&q);
}

static void test_reserve_always_reset_head(void) {
  Queue q;
  q_init(&q, 8);

  for (int i = 0; i < 6; ++i) {
    assert(q_enqueue(&q, i));
  }

  int value;

  assert(q_dequeue(&q, &value));
  assert(q_dequeue(&q, &value));
  assert(q_dequeue(&q, &value));

  assert(q.head == 3);

  assert(q_reserve(&q, 16));

  assert(q.head == 0);
  assert(q.count == 3);

  assert(q.buf[0] == 3);
  assert(q.buf[1] == 4);
  assert(q.buf[2] == 5);

  q_clean(&q);
}

static void test_reuse_after_empty(void) {
  Queue q;
  q_init(&q, 3);

  assert(q_enqueue(&q, 1));
  assert(q_enqueue(&q, 2));
  assert(q_enqueue(&q, 3));

  int value;

  assert(q_dequeue(&q, &value));
  assert(value == 1);

  assert(q_dequeue(&q, &value));
  assert(value == 2);

  assert(q_dequeue(&q, &value));
  assert(value == 3);

  assert(q.count == 0);

  // Queue sau khi empty vẫn phải sử dụng lại được
  assert(q_enqueue(&q, 100));
  assert(q_enqueue(&q, 200));

  assert(q_dequeue(&q, &value));
  assert(value == 100);

  assert(q_dequeue(&q, &value));
  assert(value == 200);

  q_clean(&q);
}

static void test_large_number_of_operations(void) {
  Queue q;
  q_init(&q, 16);

  for (int round = 0; round < 1000; ++round) {
    for (int i = 0; i < 8; ++i) {
      assert(q_enqueue(&q, round * 8 + i));
    }

    for (int i = 0; i < 8; ++i) {
      int value;

      assert(q_dequeue(&q, &value));
      assert(value == round * 8 + i);
    }
  }

  assert(q.count == 0);

  q_clean(&q);
}

int main(void) {
  test_init();
  test_enqueue_front();
  test_dequeue();
  test_fifo();
  test_empty_queue();

  test_wrap_around();
  test_multiple_wrap_around();

  test_reserve_empty_queue();
  test_reserve_with_data();
  test_reserve_after_wrap_around();
  test_reserve_always_reset_head();

  test_reuse_after_empty();
  test_large_number_of_operations();

  printf("All Queue tests passed!\n");

  return 0;
}
