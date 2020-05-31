/**
 *  @copyright Copyright (C) Katherine Skocelas, MIT Software license; see doc/LICENSE.md
 *  @date 2020.
 *
 *  @file  Population.h
 *  @brief Manages analysis of a single population.
 *  @note  Status: BETA
 *
 *  Populations are either all HOSTS or all PARASITES.
 *  - Hosts collect resources from the world.
 *  - Parasites collect resources from hosts.
 */

#pragma once 

#include "Organism.h"

#include "base/vector.h"
#include "tools/Random.h"
#include "tools/TimeQueue.h"

// class World;
class Population {

  public:

    /*************************************************************************************************************************************
    * Population constructor. Reads in arguments from the command line and uses to set up the experiment.
    * 
    * @param \c _is_parasite   Is the organism a paraste.
    * @param \c _organism_type The type of organism it is.
    * @param \c _random        Empirical random number generator.
    *************************************************************************************************************************************/
    Population(const std::string & _name, emp::Random & _random, bool _are_parasites = false, size_t _initial_pop_size = 0) 
    : random(_random), name(_name), are_parasites(_are_parasites), organism_queue(_initial_pop_size)
    { 
      size_t initial_pop_size = _initial_pop_size;

      // create starting organisms & add to population
      for (int org_count = 0; org_count < initial_pop_size; org_count++) {
        organisms.emplace_back(org_count, 2, true, random);
        ++num_organisms;
      }

    }

    // getters & setters
    const std::string GetName() { return name; }
    bool AreParasites() { return are_parasites; }
    size_t Size() { return num_organisms; }

  private:
    // references
    emp::Random & random;
    const std::string name;

    //organism variables
    emp::vector<Organism> organisms;       ///< All organisms in this population
    bool are_parasites;                    ///< Are the organisms in the population parasites?
    size_t num_organisms = 0;              ///< How many organisms are currently in the population?

    //replication variables
    emp::TimeQueue<size_t> organism_queue; ///< Organisms waiting to replicate.
    double mutation_probability = 0.0;     ///< Probability of an offspring being mutated.

};