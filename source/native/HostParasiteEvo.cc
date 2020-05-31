/**
 *  @copyright Copyright (C) Katherine Skocelas, MIT Software license; see doc/LICENSE.md
 *  @date 2020.
 *
 *  @file  HostParasiteEvo.cc
 *  @brief Examining the co-evolution of hosts and parasites.
 *  @note Status: BETA
 *
 */

#include <iostream>

#include "base/vector.h"
#include "config/command_line.h"

#include "../HostParasiteEvo.h"

// This is the main function for the NATIVE version of Host-Parasite Coevolution.

int main(int argc, char* argv[])
{
    emp::vector<std::string> args = emp::cl::args_to_strings(argc, argv);
    Experiment experiment(args);  
    experiment.Run();    
}

