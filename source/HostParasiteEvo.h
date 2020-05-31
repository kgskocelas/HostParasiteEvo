/**
 *  @copyright Copyright (C) Katherine Skocelas, MIT Software license; see doc/LICENSE.md
 *  @date 2020.
 *
 *  @file  Experiment.h
 *  @brief Manages host-parasite co-evolution experiment.
 *  @note  Status: BETA
 */

#pragma once

#include <iostream>

#include "config/command_line.h"
#include "config/SettingCombos.h"

#include "tools/StreamManager.h"
#include "tools/string_utils.h"
#include "tools/vector_utils.h"

#include "World.h"

class Experiment {

    public:
        emp::vector<std::string> args;

        emp::Random random;
        emp::SettingCombos combos;
        std::string exe_name;               ///< Name of executable used to start this run.
        World world;

        size_t gen_count = 0;               ///< Num generations to evolve (zero for analyze worlds)
        // size_t pop_size = 200;            ///< Num organisms in the population.
        bool reset_cache = false;           ///< Share the cache by default.
        bool print_reps = false;            ///< Should we print results for every replicate?
        bool print_trace = false;           ///< Should we show each step of a world?
        bool verbose = false;               ///< Should we print extra information during the run?

        emp::StreamManager stream_manager;  ///< Manage files
        std::string evolution_filename;     ///< Output filename for evolution summary data.
        std::string world_filename;         ///< Output filename for world summary data.

        // using TreatmentResults = emp::vector<RunResults>;
        // using WorldResults = emp::vector<TreatmentResults>;

        // WorldResults base_results;

        /*************************************************************************************************************************************
         * Experiment constructor. Reads in arguments from the command line and uses to set up the experiment.
         * 
         * @param \c _args Experiment settings inputted by the user.
         * 
         ************************************************************************************************************************************/
        Experiment(emp::vector<std::string> _args) : args(_args) {
            exe_name = args[0];

            // Setup all command-line options that the system should use.  In general, lower-case
            // letters are used to control model parameters, while capital letters are used to control
            // output.  The one exception is -h for '--help' which is otherwise too standard.
            // The order below sets the order that combinations are tested in. 
            // AVAILABLE OPTION FLAGS: fjklqwxyz ABCDFGHIJKNOQRSUVWXYZ

            combos.AddSetting<size_t>("data_count", "Number of times to replicate each run", 'd') = { 100 };
            combos.AddSingleSetting("gen_count",   "Num generations to evolve (0=analyze only)", 'g',
                            gen_count, "NumGens") = { 0 };

            combos.AddAction("help", "Print full list of options", 'h',
                            [this](){
                            combos.PrintHelp(exe_name, " -n 0,4,8 -r 0,1 -t 4,8,16,32 -d 100");
                            exit(1);
                            } );
            combos.AddSingleSetting("evolution_filename", "Filename for evolution data", 'E',
                                    evolution_filename, "Filename") = { "evolution.dat" };
            combos.AddAction("independent_caches", "Use a distinct cache for each run", 'i',
                            [this](){ reset_cache = true; } );
            combos.AddSingleSetting("world_filename", "Filename for world data", 'M',
                                    world_filename, "Filename") = { "world.dat" };
            combos.AddAction("print_reps", "Print data for each replicate", 'P',
                            [this](){ print_reps = true; } );
            combos.AddAction("trace", "Show each step of replicates (world or population)", 'T',
                            [this](){ print_trace = true; } );
            combos.AddAction("verbose", "Print extra information during the run", 'v',
                            [this](){ verbose = true; } );

            // Process the command-line options
            args = combos.ProcessOptions(args);

            // Fail if there are any unknown args.
            if (args.size()) {
            std::cerr << "ERROR: Unknown options: " << emp::to_string(args) << "\n";
            exit(2);
            }
        }; 

        /*************************************************************************************************************************************
         * Run an expiriment.
         ************************************************************************************************************************************/
        void Run() {
            
            emp::Random random = emp::Random();

            //1. initilize world
            World world;
        
            //2. initialize populations & add to world
            world.AddPopulation("fleas");
            world.AddPopulation("cats");
            world.AddPopulation("dogs");

            //4. run experiement
            std::cout << "Hello, host parasite evolution world!";    
        }

};