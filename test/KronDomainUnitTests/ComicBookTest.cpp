#include <gtest/gtest.h>

#include <memory>

class ComicBookFixture: public testing::Test
{
protected:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ComicBookFixture, shouldReturnTrue)
{
    EXPECT_TRUE(true);
}
