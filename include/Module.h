#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>
#include <queue>

typedef std::queue<std::string> queue_string;

/// Module base class
class Module
{

public:

  // user-given module name
  std::string m_name;

  // input strings to module
  queue_string inputs;

  /// Constructor
  Module(std::string name);

  /// Destructor
  ~Module();

  /// Process module gets overridden by child module classes
  virtual std::string process();

};


#endif /* #ifndef __MODULE_H__ */
