#ifndef __REVERSE_MODULE_H__
#define __REVERSE_MODULE_H__

#include "Module.h"

/// Reverse module
class ReverseModule : public Module
{

public:

  ReverseModule(std::string);

  /**
  * Process function returns the input string reversed.
  *
  * Example:
  *    in - "hello"
  *    out - "olleh"
  */
  virtual std::string process();

};

#endif /* #ifndef __REVERSE_MODULE_H__ */
