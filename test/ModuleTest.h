#include "Module.h"

class ModuleTest : public ::testing::Test {
 protected:

  ModuleTest() { }

  ~ModuleTest() override { }
};

// Tests name member
TEST_F(ModuleTest, process) {
  Module * m = new Module("MyModule");

  ASSERT_EQ(m->m_name, "MyModule");
}

// test set/get inputs
TEST_F(ModuleTest, set_get_inputs) {
  Module * m = new Module("MyModule");

  m->inputs.push("hello");

  auto inputs = m->inputs;

  ASSERT_EQ(inputs.size(), 1);

  ASSERT_EQ(inputs.front(), "hello");
}
