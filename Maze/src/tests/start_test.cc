#include <gtest/gtest.h>
#include "../source/eller.h"
#include "../source/models.h"

TEST(test_generate, t1) {
    Eller generator;
    model model;
    generator.start_create_maze_eller(&model, 50, 50);
    ASSERT_DOUBLE_EQ(model.size_col, 50);
    ASSERT_DOUBLE_EQ(model.size_rows, 50);
    EXPECT_TRUE(!model.first.empty());
    EXPECT_TRUE(!model.second.empty());
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
