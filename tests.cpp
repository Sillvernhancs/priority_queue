#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <string.h>

TEST(priorityqueue, priorityqueue) {
  // default constructor.
  priorityqueue<int> x;
  EXPECT_EQ(x.Size(), 0);
}
TEST(priorityqueue, enqueue) {
  priorityqueue<int> x;
  priorityqueue<string> y;
  priorityqueue<char> z;
  vector<int> tree{1000, 1000, 500,  500,  250,  250,  750, 750,
                   750,  1500, 1500, 1250, 1250, 1750, 1750};

  string str = "";
  char input = 'a';
  for (int i = 0; i < tree.size(); i++) {
    str += to_string(i);
    input++;
    z.enqueue(input, tree[i]);
    x.enqueue(i, tree[i]);
    y.enqueue(str, tree[i]);
  }

  EXPECT_EQ(x.Size(), tree.size());
  EXPECT_EQ(y.Size(), tree.size());
  EXPECT_EQ(z.Size(), tree.size());
}
TEST(priorityqueue, clear) {
  priorityqueue<int> x;
  priorityqueue<string> y;
  priorityqueue<char> z;
  vector<int> tree{1000, 1000, 500,  500,  250,  250,  750, 750,
                   750,  1500, 1500, 1250, 1250, 1750, 1750};

  string str = "";
  char input = 'a';
  for (int i = 0; i < tree.size(); i++) {
    str += to_string(i);
    input++;
    z.enqueue(input, tree[i]);
    x.enqueue(i, tree[i]);
    y.enqueue(str, tree[i]);
  }

  x.clear();
  y.clear();
  z.clear();

  EXPECT_EQ(x.Size(), 0);
  EXPECT_EQ(y.Size(), 0);
  EXPECT_EQ(z.Size(), 0);

  EXPECT_EQ(x.toString(), "");
  EXPECT_EQ(y.toString(), "");
  EXPECT_EQ(z.toString(), "");
}
TEST(priorityqueue, copy_equal) {
  priorityqueue<int> x;
  priorityqueue<string> y;
  priorityqueue<char> z;
  vector<int> tree{1000, 1000, 500,  500,  250,  250,  750, 750,
                   750,  1500, 1500, 1250, 1250, 1750, 1750};

  string str = "";
  char input = 'a';
  for (int i = 0; i < tree.size(); i++) {
    str += to_string(i);
    input++;
    z.enqueue(input, tree[i]);
    x.enqueue(i, tree[i]);
    y.enqueue(str, tree[i]);
  }

  priorityqueue<int> a;
  priorityqueue<string> b;
  priorityqueue<char> c;

  a = x;
  b = y;
  c = z;

  EXPECT_EQ(x.Size(), a.Size());
  EXPECT_EQ(y.Size(), b.Size());
  EXPECT_EQ(z.Size(), c.Size());

  EXPECT_EQ(x.toString(), a.toString());
  EXPECT_EQ(y.toString(), b.toString());
  EXPECT_EQ(z.toString(), c.toString());
}
TEST(priorityqueue, next) {
  priorityqueue<int> x;
  priorityqueue<string> y;
  priorityqueue<char> z;
  vector<int> tree{1000, 1000, 500,  500,  250,  250,  750,  750,
                   750,  1500, 1500, 1250, 1250, 1750, 1750, 2000};
  vector<int> treeODER{250,  250,  500,  500,  750,  750,  750,  1000,
                       1000, 1250, 1250, 1500, 1500, 1750, 1750, 2000};
  vector<int> val1{4, 5, 2, 3, 6, 7, 8, 0, 1, 11, 12, 9, 10, 13, 14, 15};
  vector<string> val2{"0123",
                      "01234",
                      "01",
                      "012",
                      "012345",
                      "0123456",
                      "01234567",
                      "",
                      "0",
                      "012345678910",
                      "01234567891011",
                      "012345678",
                      "0123456789",
                      "0123456789101112",
                      "012345678910111213",
                      "01234567891011121314"};
  vector<char> val3{'e', 'f', 'c', 'd', 'g', 'h', 'i', 'a',
                    'b', 'l', 'm', 'j', 'k', 'n', 'o', 'p'};

  int count = 0;
  string str = "";
  char input = 'a';
  for (int i = 0; i < tree.size(); i++) {
    z.enqueue(input, tree[i]);
    x.enqueue(count, tree[i]);
    y.enqueue(str, tree[i]);

    str += to_string(i);
    input++;
    count++;
  }
  // cout << y.toString() << endl;
  x.begin();
  y.begin();
  z.begin();

  count = 0;
  str = "";
  input = 'a';

  int value1 = 0;
  string value2 = "";
  char value3 = '\0';

  int priority1 = -9999;
  int priority2 = -9999;
  int priority3 = -9999;

  for (int i = 0; i < tree.size(); i++) {
    if (i == tree.size() - 1) {
      ASSERT_EQ(x.next(value1, priority1), false);
      ASSERT_EQ(y.next(value2, priority2), false);
      ASSERT_EQ(z.next(value3, priority3), false);
    } else {
      ASSERT_EQ(x.next(value1, priority1), true);
      ASSERT_EQ(y.next(value2, priority2), true);
      ASSERT_EQ(z.next(value3, priority3), true);
    }
    // cout << count << " COMP " << value1 << endl;
    ASSERT_EQ(treeODER[i], priority1);
    ASSERT_EQ(treeODER[i], priority2);
    ASSERT_EQ(treeODER[i], priority3);

    ASSERT_EQ(val1[i], value1);
    ASSERT_EQ(val2[i], value2);
    ASSERT_EQ(val3[i], value3);
  }
}
TEST(priorityqueue, dequeue) {
  priorityqueue<int> x;
  priorityqueue<string> y;
  priorityqueue<char> z;
  vector<int> tree{1000, 1000, 500,  500,  250,  250,  750,  750,
                   750,  1500, 1500, 1250, 1250, 1750, 1750, 2000};
  vector<int> treeODER{250,  250,  500,  500,  750,  750,  750,  1000,
                       1000, 1250, 1250, 1500, 1500, 1750, 1750, 2000};
  vector<int> val1{4, 5, 2, 3, 6, 7, 8, 0, 1, 11, 12, 9, 10, 13, 14, 15};
  vector<string> val2{"0123",
                      "01234",
                      "01",
                      "012",
                      "012345",
                      "0123456",
                      "01234567",
                      "",
                      "0",
                      "012345678910",
                      "01234567891011",
                      "012345678",
                      "0123456789",
                      "0123456789101112",
                      "012345678910111213",
                      "01234567891011121314"};
  vector<char> val3{'e', 'f', 'c', 'd', 'g', 'h', 'i', 'a',
                    'b', 'l', 'm', 'j', 'k', 'n', 'o', 'p'};

  int count = 0;
  string str = "";
  char input = 'a';
  for (int i = 0; i < tree.size(); i++) {
    z.enqueue(input, tree[i]);
    x.enqueue(count, tree[i]);
    y.enqueue(str, tree[i]);

    str += to_string(i);
    input++;
    count++;
  }
  // cout << y.toString() << endl;
  x.begin();
  y.begin();
  z.begin();

  count = 0;
  str = "";
  input = 'a';

  int value1 = 0;
  string value2 = "";
  char value3 = '\0';

  int size = tree.size() - 1;

  for (int i = 0; i < tree.size(); i++) {
    value1 = x.dequeue();
    value2 = y.dequeue();
    value3 = z.dequeue();

    EXPECT_EQ(x.Size(), size - i);
    EXPECT_EQ(y.Size(), size - i);
    EXPECT_EQ(z.Size(), size - i);

    ASSERT_EQ(val1[i], value1);
    ASSERT_EQ(val2[i], value2);
    ASSERT_EQ(val3[i], value3);
  }
}
TEST(priorityqueue, equality) {
  priorityqueue<int> x;
  priorityqueue<string> y;
  priorityqueue<char> z;
  priorityqueue<int> a;
  priorityqueue<string> b;
  priorityqueue<char> c;

  priorityqueue<int> x1;
  priorityqueue<int> x2;

  vector<int> tree{1000, 1000, 500,  500,  250,  250,  750,  750,
                   750,  1500, 1500, 1250, 1250, 1750, 1750, 2000};
  int count = 0;
  string str = "";
  char input = 'a';
  for (int i = 0; i < tree.size(); i++) {
    x.enqueue(count, tree[i]);
    y.enqueue(str, tree[i]);
    z.enqueue(input, tree[i]);

    a.enqueue(count, tree[i]);
    b.enqueue(str, tree[i]);
    c.enqueue(input, tree[i]);

    str += to_string(i);
    input++;
    count++;
  }

  EXPECT_EQ(x1 == x2, true);
  EXPECT_EQ(x == a, true);
  EXPECT_EQ(y == b, true);
  EXPECT_EQ(z == c, true);
}
TEST(priorityqueue, peak) {
  priorityqueue<int> x;
  priorityqueue<int> x1;
  priorityqueue<string> y;
  priorityqueue<char> z;
  vector<int> tree{1000, 1000, 500,  500,  250,  250,  750,  750,
                   750,  1500, 1500, 1250, 1250, 1750, 1750, 2000};
  vector<int> treeODER{250,  250,  500,  500,  750,  750,  750,  1000,
                       1000, 1250, 1250, 1500, 1500, 1750, 1750, 2000};
  vector<int> val1{4, 5, 2, 3, 6, 7, 8, 0, 1, 11, 12, 9, 10, 13, 14, 15};
  vector<string> val2{"0123",
                      "01234",
                      "01",
                      "012",
                      "012345",
                      "0123456",
                      "01234567",
                      "",
                      "0",
                      "012345678910",
                      "01234567891011",
                      "012345678",
                      "0123456789",
                      "0123456789101112",
                      "012345678910111213",
                      "01234567891011121314"};
  vector<char> val3{'e', 'f', 'c', 'd', 'g', 'h', 'i', 'a',
                    'b', 'l', 'm', 'j', 'k', 'n', 'o', 'p'};

  int value1 = 0;
  string value2 = "";
  char value3 = '\0';
  int priority;

  int count = 0;
  string str = "";
  char input = 'a';

  for (int i = 0; i < tree.size(); i++) {
    z.enqueue(input, tree[i]);
    x.enqueue(count, tree[i]);
    y.enqueue(str, tree[i]);

    str += to_string(i);
    input++;
    count++;
  }
  // cout << y.toString() << endl;
  x.begin();
  y.begin();
  z.begin();
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(x.peek(), val1[i]);
    EXPECT_EQ(y.peek(), val2[i]);
    EXPECT_EQ(z.peek(), val3[i]);

    x.dequeue();
    y.dequeue();
    z.dequeue();
  }
}
