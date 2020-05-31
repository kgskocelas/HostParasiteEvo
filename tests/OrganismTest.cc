#define CATCH_CONFIG_MAIN

#include "Catch/single_include/catch2/catch.hpp"

#include "tools/Random.h"

#include "Organism.h"

TEST_CASE("Test organism constructor")
{
  emp::Random random = emp::Random();

  Organism org = Organism(1, 2, true, random);

  REQUIRE(org.GetOrganismType() == 1);
  REQUIRE(org.GetId() == 2);
  REQUIRE(org.IsParasite());
  REQUIRE(org.GetGenome().size() == 100);  //FIXME -- change to test values with set seed
}

