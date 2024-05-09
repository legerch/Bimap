#include <gtest/gtest.h>
#include <string>

#include "bimap.h"

/*****************************/
/* Namespace instructions    */
/*****************************/

/*****************************/
/* Classes aliases           */
/*****************************/

/*****************************/
/* Define test classes       */
/*****************************/

class BimapTests : public testing::Test
{

protected:
    cmap::Bimap<int, std::string> m_mapNumberToString =
    {
        {1, "ONE"},
        {2, "TWO"},
        {3, "THREE"}
    };
};

/*****************************/
/* Defines test fixtures routines
 * (using TEST_F())            */
/*****************************/

TEST_F(BimapTests, isNotEmpty)
{
    EXPECT_FALSE(m_mapNumberToString.empty());
}

TEST_F(BimapTests, sizeIsCorrect)
{
    EXPECT_EQ(3, m_mapNumberToString.size());
}

TEST_F(BimapTests, clearResetMap)
{
    m_mapNumberToString.clear();

    EXPECT_TRUE(m_mapNumberToString.empty());
    EXPECT_EQ(0, m_mapNumberToString.size());
}

TEST_F(BimapTests, insertNewItems)
{
    m_mapNumberToString.insert(4, "FOUR");

    EXPECT_FALSE(m_mapNumberToString.empty());
    EXPECT_EQ(4, m_mapNumberToString.size());
    EXPECT_EQ("FOUR", m_mapNumberToString.getValue(4));
    EXPECT_EQ(4, m_mapNumberToString.getKey("FOUR"));
}

TEST_F(BimapTests, searchByValidKeys)
{
    EXPECT_EQ("ONE", m_mapNumberToString.getValue(1));
    EXPECT_EQ("TWO", m_mapNumberToString.getValue(2));
    EXPECT_EQ("THREE", m_mapNumberToString.getValue(3));
}

/*****************************/
/* End                       */
/*****************************/
