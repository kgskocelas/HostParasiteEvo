/**
 *  @copyright Copyright (C) Katherine Skocelas, MIT Software license; see doc/LICENSE.md
 *  @date 2020.
 *
 *  @file  World.h
 *  @brief Manages analysis of a single run in a host-parasite co-evolution world.
 *  @note  Status: BETA
 *
 */

#pragma once 

#include "Population.h"

#include "base/vector.h"
#include "tools/Random.h"
#include "tools/stats.h"
#include "tools/TimeQueue.h"

class World
{
    public:
        /*************************************************************************************************************************************
        * World constructor.
        * 
        * TODO -- add params for world dimensions 
        * TODO -- add params for world resources
        *************************************************************************************************************************************/
        World() {}

        /*************************************************************************************************************************************
        * Creates a new population and adds it to the world.
        * 
        * @param \c population_name     Name of the population.
        * @param \c init_size           Initial population size. Creates this number of random organisms & adds them to the population.
        * @param \c is_parasite         Is this a population of parasites.
        *************************************************************************************************************************************/
        void AddPopulation(const std::string &population_name, bool is_parasite = false, size_t init_size = 0)
        {
            populations.emplace_back(population_name, random, is_parasite, init_size);
        }

        //getters & setters
        int GetNumPopulations() { return populations.size(); }

    private: 
        emp::Random random;   
        //world variables

        //world contents
        emp::vector<Population> populations;

};

/// spatial map of world
struct WorldMap
{
    //map variables
};

/// Results from a single run. -- FIXME
struct RunResults
{
    double run_time;                ///< What was the replication time of this group?
    emp::vector<double> org_counts; ///< How many orgs have each bit count?

    RunResults() : run_time(0.0), org_counts(0) { ; }
    RunResults(const size_t num_bits) : run_time(0.0), org_counts(num_bits + 1, 0.0) { ; }
    RunResults(const RunResults &) = default;
    RunResults(RunResults &&) = default;

    RunResults &operator=(const RunResults &) = default;
    RunResults &operator=(RunResults &&) = default;

    RunResults &operator+=(const RunResults &in)
    {
        emp_assert(org_counts.size() == in.org_counts.size());
        run_time += in.run_time;
        for (size_t i = 0; i < org_counts.size(); i++)
            org_counts[i] += in.org_counts[i];
        return *this;
    }
};
