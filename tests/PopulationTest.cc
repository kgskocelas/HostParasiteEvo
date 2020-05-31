#define CATCH_CONFIG_MAIN

#include "Catch/single_include/catch2/catch.hpp"

#include "tools/Random.h"

#include "Population.h"

TEST_CASE("Test Population constructor")
{
  emp::Random random = emp::Random();
  const std::string name = "test";
  Population pop = Population(name, random, true, 2);

  REQUIRE(pop.GetName() == name);
  REQUIRE(pop.Size() == 2);
  REQUIRE(pop.AreParasites());
}
