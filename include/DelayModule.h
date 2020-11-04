#ifndef __DELAY_MODULE_H__
#define __DELAY_MODULE_H__

#include "Module.h"

/// Delay module
class DelayModule : public Module
{

public:

  DelayModule(std::string name);

  /**
  * Process function returns the previous input string. The string 'hello' is
  * set as initial string
  *
  * Example:
  *    in - "hello"
  *    out - "hello"
  *    in - "hey"
  *    out - "hello"
  */
  virtual std::string process();

};

#endif /* #ifndef __DELAY_MODULE_H__ */
