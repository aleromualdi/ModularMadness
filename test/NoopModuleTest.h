#include "NoopModule.h"

class NoopModuleTest : public ::testing::Test {
 protected:

  NoopModuleTest() { }

  ~NoopModuleTest() override { }

};

// test module name
TEST_F(NoopModuleTest, m_name) {

  NoopModule * m = new NoopModule("MyModule");

  ASSERT_EQ(m->m_name, "MyModule");
}

// test process
TEST_F(NoopModuleTest, process) {
  NoopModule * m = new NoopModule("MyModule");

  m->inputs.push("hello");

  auto p = m->process();

  ASSERT_EQ(p, "hello");
}
