#include "EchoModule.h"

class EchoModuleTest : public ::testing::Test {
 protected:

  EchoModuleTest() { }

  ~EchoModuleTest() override { }

};

// test module name
TEST_F(EchoModuleTest, m_name) {

  EchoModule * m = new EchoModule("MyModule");

  ASSERT_EQ(m->m_name, "MyModule");
}

// test process
TEST_F(EchoModuleTest, process) {
  EchoModule * m = new EchoModule("MyModule");

  m->inputs.push("hello");

  auto p = m->process();

  ASSERT_EQ(p, "hello hello");
}
