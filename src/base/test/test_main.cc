#include "glog/logging.h"
#include "gtest/gtest.h"

int main(int argc, char* argv[]) {
  google::InstallFailureSignalHandler();
  ::testing::InitGoogleTest(&argc, argv);
  google::ParseCommandLineFlags(&argc, &argv, /*remove_flags=*/true);
  return RUN_ALL_TESTS();
}