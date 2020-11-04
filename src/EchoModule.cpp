#include "EchoModule.h"

EchoModule::EchoModule(std::string name) : Module(name)
{

}

std::string EchoModule::process()
{
  auto out = this->inputs.front() + " " + this->inputs.front();

  this->inputs.pop();

  return out;
}
