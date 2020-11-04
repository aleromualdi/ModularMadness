#ifndef __NOOP_MODULE_H__
#define __NOOP_MODULE_H__

#include "Module.h"

/// noopp module
class NoopModule : public Module
{

public:

  NoopModule(std::string);

  /**
  * Process function returns the input string.
  *
  * Example:
  *    in - "hello"
  *    out - "hello"
  */
  virtual std::string process();
};

#endif /* #ifndef __NOOP_MODULE_H__ */
