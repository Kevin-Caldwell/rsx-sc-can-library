#include <circular_buffer.h>

using Buffer = CircularBuffer<int, 8>;
using Test = bool (*)();

bool test_push_one()
{
  Buffer b;
  b.push(1);
  return b.elements() == 1;
}

bool test_push_multiple()
{
  Buffer b;
  for (int i = 0; i < 3; i++) {
    b.push(i);
  }
  return b.elements() == 3 &&
    b[0] == 0 &&
    b[1] == 1 &&
    b[2] == 2;
}

bool test_push_fill()
{
  Buffer b;
  for (int i = 0; i < 8; i++) {
    b.push(i);
  }

  bool validate = true;
  if (b.elements() != 8) validate = false;
  for (int i = 0; i < 8; i++) {
    if (b[i] != i) validate = false;
  }
  return validate;
}

bool test_empty_no_op()
{
  Buffer b;
  return b.empty();
}

bool test_empty_add_sub()
{
  Buffer b;
  for (int i = 0; i < 3; i++) {
    b.push(i);
  }
  for (int i = 0; i < 3; i++) {
    b.pop();
  }
  return b.empty();
}

bool test_pop_one()
{
  Buffer b;
  b.push(10);
  return b.pop() == 10 && b.elements() == 0;
}

bool test_pop_order()
{
  Buffer b;
  for (int i = 0; i < 8; i++) {
    b.push(i);
  }
  bool validate = true;
  for (int i = 0; i < 8; i++) {
    if (b.pop() != i) validate = false;
  }
  return validate;
}

void test_full()
{
  Buffer b;
  bool validate = true;

  for (int i = 0; i < 8; i++) {
    if (b.full()) {
      validate = false;
    }

    b.push(i);
  }
  if (!b.full()) {
    validate = false;
  }
  delay(5);

  return validate;
}

bool test_last()
{
  Buffer b;
  bool validate = true;

  for (int i = 0; i < 8; i++) {
    b.push(i);
    if (b.last() != b.pop()) {
      validate = false;
    }
  }

  return validate;
}

Test tests[] = {test_push_one,
  test_push_multiple,
  test_push_fill,
  test_empty_no_op,
  test_empty_add_sub,
  test_pop_one,
  test_pop_order,
  test_full,
  test_last};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Tests");
  for (int i = 0; i < sizeof(tests) / sizeof(Test); i++) {
    Serial.print("TEST ");
    Serial.print(i);
    if (!tests[i]()) {
      Serial.println(" FAILED");
    } else {
      Serial.println(" PASSED");
    }
  }
}


void loop() {
}
