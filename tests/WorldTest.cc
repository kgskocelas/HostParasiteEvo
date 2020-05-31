#define CATCH_CONFIG_MAIN

#include "Catch/single_include/catch2/catch.hpp"

#include "tools/Random.h"

#include "World.h"

TEST_CASE("Test World constructor")
{
  emp::Random random = emp::Random();

  const std::string name = "test";
  Population pop = Population(name, random, true, 1);

  World world = World();
  world.AddPopulation(pop);

  REQUIRE(world.GetNumPopulations() == 1);
}