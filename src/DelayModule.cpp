#include "DelayModule.h"

DelayModule::DelayModule(std::string name) : Module(name)
{
}

std::string DelayModule::process()
{
  auto out = this->inputs.front();

  this->inputs.pop();

  return out;
}
