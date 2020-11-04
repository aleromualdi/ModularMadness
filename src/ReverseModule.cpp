#include "ReverseModule.h"
#include <algorithm>

ReverseModule::ReverseModule(std::string name) : Module(name)
 {

 }

std::string ReverseModule::process()
{
  // Reverse the string in front of inputs
  auto out = this->inputs.front();
  for(int i = 0; i < out.length(); i++)
  {
    out[i] = this->inputs.front()[out.length() - i - 1];
  }

  this->inputs.pop();
  return out;
}
