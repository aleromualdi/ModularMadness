// Include modules
#include "ModularMadness.h"

using namespace std;


std::vector<Module *> ModularMadness::modules;
int ModularMadness::numModules = 0;
int_vec_2d ModularMadness::modConnections;
int ModularMadness::availableOutputs = 0;


void ModularMadness::reset()
{

  ModularMadness::modules.clear();

  // reset module connections
  ModularMadness::modConnections.clear();

  numModules = 0;
  availableOutputs = 0;
}

void ModularMadness::initModConnections(int num_modules)
{

  // populate modConnections with -1
  for(int i=0; i<num_modules; i++) {
    modConnections.push_back(std::vector<int>());
    for(int j=0; j<num_modules; j++) {
        modConnections[i].push_back(-1);
    }
  }
}

str_vec ModularMadness::tokenizeLine(string input_line)
{
  // Tokenize the input strings
  istringstream iss(input_line);
  vector<string> tokens{istream_iterator<string>{iss},
                  istream_iterator<string>{}};

  return tokens;
}

bool ModularMadness::modulesNotEmpty()
{

  for(int i = 0; i < numModules; i++)
  {
  	if(!modules[i]->inputs.empty())
  		return true;
  }
  return false;
}

void ModularMadness::defineModule(string name, string operation)
{

  if (operation == "echo") {
    // create EchoModule and add it to modules array
    EchoModule * em = new EchoModule(name);
    modules.push_back(em);
  }

  else if (operation == "delay") {
    // create DelayModule and add it to modules array
    DelayModule * dm = new DelayModule(name);
    // define initial output for delay module
    dm->inputs.push("hello");
    modules.push_back(dm);
  }

  else if (operation == "noop") {
    // create NoopModule and add it to modules array
    NoopModule * nm = new NoopModule(name);
    modules.push_back(nm);
  }

  else if (operation == "reverse") {
    // create ReverseModule and add it to modules array
    ReverseModule * rm = new ReverseModule(name);
    modules.push_back(rm);
  }

  numModules++;

  initModConnections(numModules);
}

void ModularMadness::connectModules(string module_name1, string module_name2)
{
  int idx1 = -1; //index of module with name module_name1 in modules array
  int idx2 = -1; //index of module with name module_name2 in modules array

  //find idx1, idx2
  for(int i = 0; i <= numModules; i++) {
    if(module_name1.compare(modules[i]->m_name) == 0) idx1 = i;
    if(module_name2.compare(modules[i]->m_name) == 0) idx2 = i;
    if(idx1 != -1 && idx2 != -1) break;
  }

  // find correct 2nd index.
  int c = 0;
  while(modConnections[idx1][c] != -1 && c < 10) c++;
  modConnections[idx1][c] = idx2;
}

void ModularMadness::processWord(std::string word)
{

  std::string output;
  std::queue<int> modQ;
  int currentMod = 0;
  modQ.push(0);

  Module * tempMod = modules[0];
  tempMod->inputs.push(word);

  while(true) {
  	if(modQ.empty()) break;

  	tempMod = modules[modQ.front()];
  	currentMod = modQ.front();
  	modQ.pop();
  	output = tempMod->process();
  	int i = 0;

  	// if currentMod is at end of chain, process, print, and continue.
  	if(modConnections[currentMod][0] == -1)
    {
      vector<string> tokens = tokenizeLine(output);
      vector<string>::iterator it;

      for (it = tokens.begin(); it != tokens.end(); it++)
      {
        if(availableOutputs<=0) break;
        cout << *it << " ";
        // update available number output
        availableOutputs -= 1;
      }
      continue;
  	}

  	// traverse module connections, push them to modQ for later processing.
  	while(modConnections[currentMod][i] != -1)
    {
  		if(output.compare("") != 0) {
  			Module * sendTo = modules[modConnections[currentMod][i]];

        if(sendTo->inputs.empty() == 1 || sendTo->m_name == "delay") {
  				sendTo->inputs.push(output);
  			} else {
		      if(sendTo->inputs.front().back() == ' ') {
            // sendTo->inputs.front() += " " + output;
	          sendTo->inputs.front() += output;
  				} else {
  					sendTo->inputs.front() += " " + output;
  				}
  			}
  		}

  		// conditional prevents repeated consecutive evaluations of the same module
  		if(modQ.back() != modConnections[currentMod][i])
      {
  			modQ.push(modConnections[currentMod][i]);
  		}
  		i++;
  	}
  }
}

void ModularMadness::handleModuleCommand()
{

  // Read module name
  string name;
  cin >> name;

  // Read module operation
  string operation;
  cin >> operation;

  defineModule(name, operation);
}

void ModularMadness::handleConnectCommand()
{

  // read first module name
  string module_name1;
  cin >> module_name1;

  // read second module name
  string module_name2;
  cin >> module_name2;

  // connect modules
  connectModules(module_name1, module_name2);
}

void ModularMadness::handleProcessCommand(string input_line)
{
  // tokenize input line
  str_vec word_tokens = tokenizeLine(input_line);
  // count token words
  int numInputWords = word_tokens.size();

  // max number of output words is sixteen times the number of input words
  availableOutputs = 16 * numInputWords;

  for (int i=0; i < numInputWords; i++) {
    std::string word = word_tokens.at(i);
    processWord(word);
  }

  // clear the modules after all words are processed by processing empty string
  while(modulesNotEmpty()) {
     processWord("");
   }
}

void ModularMadness::loop()
{

  while(true)
  {

    string command;
    cin >> command;

    if (command == "module") {
      handleModuleCommand();
    } else if (command == "connect") {
      handleConnectCommand();
    } else if (command == "process") {
      // Get the input strings
      string input_line;
      getline(cin, input_line);

      // handle the "process" command
      handleProcessCommand(input_line);

      // output new line character
      cout << endl;
    }
    else if (command ==  "exit") break;
    else {
  		printf("unknown command, try again\n");
  	}
  }
}
