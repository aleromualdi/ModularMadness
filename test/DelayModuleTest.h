#include "DelayModule.h"

class DelayModuleTest : public ::testing::Test {
 protected:

  DelayModuleTest() { }

  ~DelayModuleTest() override { }

};

// test module name
TEST_F(DelayModuleTest, m_name) {

  DelayModule * m = new DelayModule("MyModule");

  ASSERT_EQ(m->m_name, "MyModule");
}

// test process
TEST_F(DelayModuleTest, process) {

  DelayModule * m = new DelayModule("MyModule");
  // set initial input
  m->inputs.push("hello");

  m->inputs.push("hello");
  auto p1 = m->process();
  ASSERT_EQ(p1, "hello");

  m->inputs.push("world");
  auto p2 = m->process();
  ASSERT_EQ(p2, "hello");

  m->inputs.push("");
  auto p3 = m->process();
  ASSERT_EQ(p3, "world");

  m->inputs.push("");
  auto p4 = m->process();
  ASSERT_EQ(p4, "");
}
