#ifndef __ECHO_MODULE_H__
#define __ECHO_MODULE_H__

#include "Module.h"

/// Echo module
class EchoModule : public Module
{

public:

  EchoModule(std::string);

  /**
  * Process function returns the echo of the input string.
  *
  * Example:
  *    in - "hello"
  *    out - "hello hello"
  */
  virtual std::string process();

};

#endif /* #ifndef __ECHO_MODULE_H__ */
