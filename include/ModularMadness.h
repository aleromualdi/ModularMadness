#ifndef __MODULAR_MADNESS_H__
#define __MODULAR_MADNESS_H__

// includes
#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <vector>
#include <iterator>

// include modules
#include "Module.h"
#include "DelayModule.h"
#include "EchoModule.h"
#include "NoopModule.h"
#include "ReverseModule.h"

typedef std::vector<std::string> str_vec;
typedef std::vector<std::vector<int>> int_vec_2d;


/// Modular Madness class
class ModularMadness
{

public:

  /// Constructor
  ModularMadness() ;

  /// Destructor
  ~ModularMadness() ;

  // array of pointers to Module objects, populated in order of module creation
  static std::vector<Module *> modules;

  // number of modules added in modules array
  static int numModules;

  // max number of output strings
  static int availableOutputs;

  // arry of integers representing connections between modules
  static int_vec_2d modConnections;

  /**
  * Initialize 2d arry of integers representing connections between modules.
  * They are initialized with -1, to signify no module connection.
  *
  * @param num_modules number of modules
  */
  static void initModConnections(int num_modules);

  /**
  * Reset ModularMadness.
  */
  static void reset();

  /**
  * Get module array.
  *
  * @return vector of pointers to Module objects
  */
  static std::vector<Module *> getModules()
  {
   return modules;
  }

  /**
  * Get number of defined modules.
  *
  * @return number of modules
  */
  static int getNumModules()
  {
    return numModules;
  }

  /**
  * Get number of available output strings.
  *
  * @return number of available output strings
  */
  static int getAvailableOutputs()
  {
    return availableOutputs;
  }

  /**
  * Get module connections.
  *
  * Example:
  *   modConnections[0][3] = 5 means module 0 has 4 connections and the fourth
  *   connection is with the firth module defined in 'modules' array.
  *
  * @return modConnections 2d vector representing connections between modules
  */
  static int_vec_2d getModConnections()
  {
    return modConnections;
  }

  /**
  * Tokenize the input line string.
  *
  * @param input_line input line string
  * @return vector of strings (tokens)
  */
  static str_vec tokenizeLine(std::string input_line);

  /**
  * Define module.
  *
  * @param name arbitrary name of the module
  * @param operation specifies what the module should do with its input
  */
  static void defineModule(std::string name, std::string operation);

  /**
  * Connects the output of one module to the input of another.
  *
  * @param module_name1 name of the first module
  * @param module_name2 name of the second module
  */
  static void connectModules(std::string module_name1, std::string module_name2);

  /**
  * Process single word string through the defined module network.
  */
  static void processWord(std::string str);

  /**
  * Handler method for procesing input line.
  *
  * @param input_line input line string
  */
  static void handleProcessCommand(std::string input_line);

  /**
  * Check if not all modules are empty.
  *
  * @return bool return true if not all modules are empty
  */
  static bool modulesNotEmpty();

  /**
  * Loop on standard input.
  */
  static void loop();

private:

  /// Handle the "module" command
  static void handleModuleCommand();

  /// Handle the "connect" command
  static void handleConnectCommand();

};

#endif /* #ifndef __MODULAR_MADNESS_H__ */
