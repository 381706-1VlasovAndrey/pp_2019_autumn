// Copyright 2019 Vlasov Andrey
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "./star_topology.h"

TEST(star_topology_MPI, test1_can_create_StarTopology) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    ASSERT_NO_THROW(createStarComm(MPI_COMM_WORLD));
  }
}

TEST(star_topology_MPI, test2_check_StarComm_is_StarTopology) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm StarComm = createStarComm(MPI_COMM_WORLD);
  if (rank == 0) {
    EXPECT_TRUE(isStarTopology(StarComm));
  }
}

TEST(star_topology_MPI, test3_check_MPI_COMM_WORLD_is_StarTopology) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    EXPECT_FALSE(isStarTopology(MPI_COMM_WORLD));
  }
}

TEST(star_topology_MPI, test4_test_communications_MPI_COMM_WORLD) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    EXPECT_FALSE(testStarTopology(MPI_COMM_WORLD));
  }
}

TEST(star_topology_MPI, test5_test_communications_StarTopology) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  bool res = testStarTopology(MPI_COMM_WORLD);
  if (rank == 0) {
    EXPECT_TRUE(res);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
