#include "ModularMadness.h"

typedef std::vector<std::string> str_vec;


class ModularMadnessTest : public ::testing::Test {
 protected:

  ModularMadnessTest() { }

  ~ModularMadnessTest() override { }

};


/**
* Test getModules method.
*/
TEST_F(ModularMadnessTest, get_modules) {

  // simulates standard input: "module alpha noop"
  ModularMadness::defineModule("alpha", "noop");

  // simulates standard input: "module beta noop"
  ModularMadness::defineModule("beta", "noop");

  // get modules
  auto modules = ModularMadness::getModules();

  ASSERT_EQ(modules[0]->m_name, "alpha");

  ASSERT_EQ(modules[1]->m_name, "beta");

  // reset
  ModularMadness::reset();
}

/**
* Test getNumModules method.
*/
TEST_F(ModularMadnessTest, get_num_modules) {

  // simulates standard input: "module alpha reverse"
  ModularMadness::defineModule("alpha", "reverse");

  // simulates standard input: "module beta delay"
  ModularMadness::defineModule("beta", "delay");

  // get current number of modules
  auto currentNumModules = ModularMadness::getNumModules();

  ASSERT_EQ(currentNumModules, 2);

  // reset ModularMadness
  ModularMadness::reset();
}

/**
* Test init modConnections.
*/
TEST_F(ModularMadnessTest, init_module_connections) {
  // initialzie module connections
  ModularMadness::initModConnections(10);

  // get module connections
  auto currModuleConnections = ModularMadness::getModConnections();

  // check that all module connections are set to -1
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      ASSERT_EQ(currModuleConnections[i][j], -1);
    }
  }

  // reset
  ModularMadness::reset();
}

/**
* Test ModuleConnections.
*/
TEST_F(ModularMadnessTest, module_connections) {

  // ToDO check that model conenctions at all -1 here.

  // simulates standard input: "module alpha noop"
  ModularMadness::defineModule("alpha", "noop");

  // simulates standard input: "module beta noop"
  ModularMadness::defineModule("beta", "noop");

  // simulates standard input: "connect alpha beta"
  ModularMadness::connectModules("alpha", "beta");

  // get current number of modules
  auto currentNumModules = ModularMadness::getNumModules();

  // get module connections
  auto moduleConnections = ModularMadness::getModConnections();

  for(int i = 0; i < currentNumModules; i++) {
    for(int j = 0; j < currentNumModules; j++) {
      if (i == 0 && j == 0)
      {
        ASSERT_EQ(moduleConnections[i][j], 1);
      }
      else
      {
        ASSERT_EQ(moduleConnections[i][j], -1);
      }
  }
}
// reset
ModularMadness::reset();
}

/**
* Test ModuleConnections with traverse connections.
*
* Example:
*  module a reverse
*  module b delay
*  module c delay
*  module d reverse
*  connect a b
*  connect a c
*  connect c d
*  connect d b
*/
TEST_F(ModularMadnessTest, module_connections_traverse) {

  // simulates standard input: "module a reverse"
  ModularMadness::defineModule("a", "reverse");

  // simulates standard input: "module b delay"
  ModularMadness::defineModule("b", "delay");

  // simulates standard input: "connect c delay"
  ModularMadness::defineModule("c", "delay");

  // simulates standard input: "connect d reverse"
  ModularMadness::defineModule("d", "reverse");

  // simulates standard input: "connect d b"
  ModularMadness::connectModules("a", "b");

  // simulates standard input: "connect a c"
  ModularMadness::connectModules("a", "c");

  // simulates standard input: "connect c d"
  ModularMadness::connectModules("c", "d");

  // simulates standard input: "connect d b"
  ModularMadness::connectModules("d", "b");

  // get current number of modules
  auto currentNumModules = ModularMadness::getNumModules();

  auto moduleConnections = ModularMadness::getModConnections();

  for(int i = 0; i < currentNumModules; i++) {
    for(int j = 0; j < currentNumModules; j++) {

      int gg = moduleConnections[i][j];

      if (i == 0 && j == 0)
      {
        ASSERT_EQ(moduleConnections[i][j], 1);
      }
      else if (i == 0 && j == 1)
      {
        ASSERT_EQ(moduleConnections[i][j], 2);
      }
      else if (i == 2 && j == 0)
      {
        ASSERT_EQ(moduleConnections[i][j], 3);
      }
      else if (i == 3 && j == 0)
      {
        ASSERT_EQ(moduleConnections[i][j], 1);
      }
      else
      {
        ASSERT_EQ(moduleConnections[i][j], -1);
      }
  }

}

  // reset
  ModularMadness::reset();
}

/**
* Test getAvailableOutputs method.
*/
TEST_F(ModularMadnessTest, get_available_outputs) {

  // simulates standard input: "module alpha noop"
  ModularMadness::defineModule("alpha", "noop");

  // simulates standard input: "module beta noop"
  ModularMadness::defineModule("beta", "noop");

  // simulates standard input: "connect alpha beta"
  ModularMadness::connectModules("alpha", "beta");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world");

  // Get the captured output
  std::string output = testing::internal::GetCapturedStdout();

  // get current number of modules
  auto availableOutputs = ModularMadness::getAvailableOutputs();

  // the expected max number of output words is 16 * 2 = 32.
  // as two words have already printed out we are left with 30
  ASSERT_EQ(availableOutputs, 30);

  // Now check that when processing new line the availableOutputs updates

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process heyo dude wassup"
  ModularMadness::handleProcessCommand("I play music");

  // Get the captured output
  std::string output_second = testing::internal::GetCapturedStdout();

  // get current number of modules
  auto availableOutputs_second = ModularMadness::getAvailableOutputs();

  // the expected max number of output words is 16 * 3 = 48.
  // as three words have already printed out we are left with 45
  ASSERT_EQ(availableOutputs_second, 45);

  // reset
  ModularMadness::reset();
}

/**
* Test tokenizeLine method.
*/
TEST_F(ModularMadnessTest, tokenize_line) {

  // tokenize line
  str_vec tokens = ModularMadness::tokenizeLine("hello world");

  ASSERT_EQ(tokens[0], "hello");

  ASSERT_EQ(tokens[1], "world");

}

/**
* Test reset ModularMadness.
*/
TEST_F(ModularMadnessTest, reset) {

  // simulates standard input: "module alpha reverse"
  ModularMadness::defineModule("alpha", "reverse");

  // simulates standard input: "module beta delay"
  ModularMadness::defineModule("beta", "delay");

  // simulates standard input: "connect alpha beta"
  ModularMadness::connectModules("alpha", "beta");

  // reset ModularMadness
  ModularMadness::reset();

  // get current number of modules
  auto currentNumModules = ModularMadness::getNumModules();

  ASSERT_EQ(currentNumModules, 0);

  // get current modules
  auto currentModules = ModularMadness::getModules();

  // check that current modules vector is empty
  ASSERT_EQ(currentModules.empty(), true);

  // check that current module connections vector is empty
  ASSERT_EQ(ModularMadness::getModConnections().empty(), true);

}

/**
* Test process on example.
*
* Input:
*   module alpha reverse
*   module beta delay
*   connect alpha beta
*   process hello world
* Output:
*   hello olleh dlrow
*/
TEST_F(ModularMadnessTest, process) {

  // simulates standard input: "module alpha reverse"
  ModularMadness::defineModule("alpha", "reverse");

  // simulates standard input: "module beta delay"
  ModularMadness::defineModule("beta", "delay");

  // simulates standard input: "connect alpha beta"
  ModularMadness::connectModules("alpha", "beta");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world");

  // Assert equal to the expect example output
  ASSERT_EQ(testing::internal::GetCapturedStdout(), "hello olleh dlrow ");

  // Reset the ModularMadness class
  ModularMadness::reset();

}

/**
* Test double process on example.
*
* Input:
*   module alpha reverse
*   module beta delay
*   connect alpha beta
*   process hello world
* Output:
*   hello olleh dlrow
* Input
*   process hello world
*   olleh dlrow
*/
TEST_F(ModularMadnessTest, double_process) {

  // simulates standard input: "module alpha reverse"
  ModularMadness::defineModule("alpha", "reverse");

  // simulates standard input: "module beta delay"
  ModularMadness::defineModule("beta", "delay");

  // simulates standard input: "connect alpha beta"
  ModularMadness::connectModules("alpha", "beta");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world");

  // Get the captured output
  std::string output = testing::internal::GetCapturedStdout();

  // Assert equal to the expect example output
  ASSERT_EQ(output, "hello olleh dlrow ");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world");

  // Get the captured output
  output = testing::internal::GetCapturedStdout();

  // Assert equal to the expect example output
  ASSERT_EQ(output, "olleh dlrow ");

  // Reset the ModularMadness class
  ModularMadness::reset();

}

/**
* Tests that multiple process lines should behave the same way as if input alone.
"
* Example Input
*   module a echo
*   module b echo
*   module c echo
*   connect a b
*   connect b c
*   process hello world
* Output
*   hello hello hello hello hello hello hello hello world world world world world world world world
*   process hello world
* Output
*   hello hello hello hello hello hello hello hello world world world world world world world world
*/
TEST_F(ModularMadnessTest, multiple_proecss_lines) {

  // simulates standard input: "module a echo"
  ModularMadness::defineModule("a", "echo");

  // simulates standard input: "module b echo"
  ModularMadness::defineModule("b", "echo");

  // simulates standard input: "module c echo"
  ModularMadness::defineModule("c", "echo");

  // simulates standard input: "connect a b"
  ModularMadness::connectModules("a", "b");

  // simulates standard input: "connect b c"
  ModularMadness::connectModules("b", "c");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world ");

  // Get the captured output
  std::string output = testing::internal::GetCapturedStdout();

  // Assert equal to the expect example output
  ASSERT_EQ(output, "hello hello hello hello hello hello hello hello world world world world world world world world ");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world");

  // Get the captured output
  output = testing::internal::GetCapturedStdout();

  // Assert equal to the expect example output
  ASSERT_EQ(output, "hello hello hello hello hello hello hello hello world world world world world world world world ");

  // Reset the ModularMadness class
  ModularMadness::reset();

}

/**
* Test that noop module does not change the input.
*
* Example Input
*   module a noop
*   module b noop
*   connect a b
*   process hello world
* Output
*   hello world
*/
TEST_F(ModularMadnessTest, two_noops) {

  // simulates standard input: "module a noop"
  ModularMadness::defineModule("a", "noop");

  // simulates standard input: "module b noop"
  ModularMadness::defineModule("b", "noop");

  // simulates standard input: "connect a b"
  ModularMadness::connectModules("a", "b");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world");

  // Get the captured output
  std::string output = testing::internal::GetCapturedStdout();

  // Assert equal to the expect example output
  ASSERT_EQ(output, "hello world ");

  // Reset the ModularMadness class
  ModularMadness::reset();

}

/**
* Tests that the number of output strings is limited to sixteen times
* the number of input strings in the corresponding process line.
*
* Example Input
* module a echo
* module b echo
* module c echo
* module d echo
* module e echo
* module f echo
* module g echo
* connect a b
* connect b c
* connect c d
* connect d e
* connect e f
* connect f g
* process hello world
* Output
*   hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello
*/
TEST_F(ModularMadnessTest, max_output) {

  // simulates standard input: "module a echo"
  ModularMadness::defineModule("a", "echo");

  // simulates standard input: "module b echo"
  ModularMadness::defineModule("b", "echo");

  // simulates standard input: "module c echo"
  ModularMadness::defineModule("c", "echo");

  // simulates standard input: "module d echo"
  ModularMadness::defineModule("d", "echo");

  // simulates standard input: "module e echo"
  ModularMadness::defineModule("e", "echo");

  // simulates standard input: "module f echo"
  ModularMadness::defineModule("f", "echo");

  // simulates standard input: "module g echo"
  ModularMadness::defineModule("g", "echo");

  // simulates standard input: "connect a b"
  ModularMadness::connectModules("a", "b");

  // simulates standard input: "connect b c"
  ModularMadness::connectModules("b", "c");

  // simulates standard input: "connect c d"
  ModularMadness::connectModules("c", "d");

  // simulates standard input: "connect d e"
  ModularMadness::connectModules("d", "e");

  // simulates standard input: "connect e f"
  ModularMadness::connectModules("e", "f");

  // simulates standard input: "connect f g"
  ModularMadness::connectModules("f", "g");

  // Start capturing standard out
  testing::internal::CaptureStdout();

  // simulates standard input: "process hello world"
  ModularMadness::handleProcessCommand("hello world");

  // Get the captured output
  std::string output = testing::internal::GetCapturedStdout();

  std::vector<std::string> tokens = ModularMadness::tokenizeLine(output);

  // Assert equal to the expect example output
  ASSERT_EQ(tokens.size(), 32);

  // Reset the ModularMadness class
  ModularMadness::reset();

}
