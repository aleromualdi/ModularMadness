#include "ReverseModule.h"

class ReverseModuleTest : public ::testing::Test {
 protected:

  ReverseModuleTest() { }

  ~ReverseModuleTest() override { }

};

// test module name
TEST_F(ReverseModuleTest, m_name) {

  ReverseModule * m = new ReverseModule("MyModule");

  ASSERT_EQ(m->m_name, "MyModule");
}

// test process
TEST_F(ReverseModuleTest, process) {
  ReverseModule * m = new ReverseModule("MyModule");

  m->inputs.push("hello");

  auto p = m->process();

  ASSERT_EQ(p, "olleh");
}
