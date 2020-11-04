#include "NoopModule.h"

NoopModule::NoopModule(std::string name) : Module(name)
{
  
}

std::string NoopModule::process()
{
  auto out = this->inputs.front();

  this->inputs.pop();

  return out;
}
