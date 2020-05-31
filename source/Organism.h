/**
 *  @copyright Copyright (C) Katherine Skocelas, MIT Software license; see doc/LICENSE.md
 *  @date 2020.
 *
 *  @file  Organism.h
 *  @brief Manages analysis of a single organism.
 *  @note  Status: BETA
 *
 *  Organisms are either HOSTS or PARASITES.
 *  - Hosts collect resources from the world.
 *  - Parasites collect resources from hosts.
 */

#pragma once 

#include "tools/Random.h"

/// Information about a single organism
class Organism {

  public:
    /*************************************************************************************************************************************
    * Organism constructor. Creates a new organism with a randome genome.
    * 
    * @param \c _organism_type The type of organism it is.
    * @param \c _id            Organism id.
    * @param \c _is_parasite   Is the organism a paraste.
    * @param \c _random        Empirical random number generator.
    *************************************************************************************************************************************/
    Organism(const size_t _organism_type, const size_t _id, const bool _is_parasite, emp::Random & _random) 
    : random(_random),  organism_type(_organism_type), id(_id), is_parasite(_is_parasite)
    {

      switch(organism_type) {
        case (1) :
          create_genome(0.5);
          break;
        default : 
          /// throw an exception
          ;
      }
      
      if (is_parasite) {
        /// parasite-specific setup
      }
      else {
        /// host-specific setup
      }
    };

    /// getters & setters
    size_t GetOrganismType() { return organism_type; }
    size_t GetId() { return id; }
    std::bitset<100> GetGenome() {return genome; }
    bool IsParasite() { return is_parasite; }
    double GetReproTime() { return repro_time; }

    /// operators
    bool operator==(const Organism & _in) const { return id == _in.id; } ///< When using == on Organisms, compare their id's
    bool operator!=(const Organism & _in) const { return id != _in.id; } ///< When using != on Organisms, compare their id's
    bool operator<(const Organism & _in) const {                         ///< When using < on Organisms, compare their repro_time's
      if (repro_time == _in.repro_time) return (id < _in.id);
      return (repro_time < _in.repro_time);
    }

    //TODO - Update method
    //TODO - Reproduce method

  private:
    emp::Random & random;

    const size_t organism_type;    
    const size_t id;   
    const bool is_parasite = false;  
    std::bitset<100> genome;
    double repro_time = 0.0;          ///< When will this organism replicate?

    /*************************************************************************************************************************************
    * Generates a random 100 bit genome and assigns to this organism.
    * 
    * Uses a Bernoulli distribution: 
    * https://stackoverflow.com/questions/25176423/c-efficient-way-to-generate-random-bitset-with-configurable-mean-1s-to-0s
    * 
    * @param \c seed Random number seed.
    * @param \c p    Probability that a bit will be 1.
    ************************************************************************************************************************************/
    void create_genome(double p) {

      // genome = emp::RandomBitVector(random, 100);

      std::random_device rd;
      std::mt19937 generator(rd());
      std::bernoulli_distribution distribution(p);

      for( int n = 0; n < genome.size(); ++n) {
        genome[n] = distribution(generator);
      }

    }
  
};