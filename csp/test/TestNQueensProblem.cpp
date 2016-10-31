
#include "../NQueensCspProblem.h"

#include <gtest/gtest.h>

#include <vector>
#include <memory>

class NQueensCspProblemTester
{
public:
    NQueensCspProblemTester(const std::shared_ptr<NQueensCspProblem>& problemPtr) :
        m_problemPtr(problemPtr)
    {}

    NQueensCspProblem::State GetInitialState()
    {
        return m_problemPtr->GetInitialState();
    }

    void RemoveValueFromVar(NQueensCspProblem::State& state, const std::size_t index, const std::size_t value)
    {
        m_problemPtr->RemoveValueFromVar(state, index, value);
    }

private:
    std::shared_ptr<NQueensCspProblem> m_problemPtr;
};

TEST(NQueensProblemTest, RemoveValue)
{
    auto problemPtr = std::make_shared<NQueensCspProblem>(4);
    auto tester = NQueensCspProblemTester(problemPtr);
    auto state = tester.GetInitialState();

    ASSERT_EQ(state[0].size(), 4);
    ASSERT_EQ(state[0][0], 0);
    ASSERT_EQ(state[0][1], 1);
    ASSERT_EQ(state[0][2], 2);
    ASSERT_EQ(state[0][3], 3);
    ASSERT_EQ(state[1].size(), 4);
    ASSERT_EQ(state[1][0], 0);
    ASSERT_EQ(state[1][1], 1);
    ASSERT_EQ(state[1][2], 2);
    ASSERT_EQ(state[1][3], 3);
    ASSERT_EQ(state[2].size(), 4);
    ASSERT_EQ(state[2][0], 0);
    ASSERT_EQ(state[2][1], 1);
    ASSERT_EQ(state[2][2], 2);
    ASSERT_EQ(state[2][3], 3);
    ASSERT_EQ(state[3].size(), 4);
    ASSERT_EQ(state[3][0], 0);
    ASSERT_EQ(state[3][1], 1);
    ASSERT_EQ(state[3][2], 2);
    ASSERT_EQ(state[3][3], 3);

    tester.RemoveValueFromVar(state, 0, 2);

    ASSERT_EQ(state[0].size(), 3);
    ASSERT_EQ(state[0][0], 0);
    ASSERT_EQ(state[0][1], 1);
    ASSERT_EQ(state[0][2], 3);
    ASSERT_EQ(state[1].size(), 4);
    ASSERT_EQ(state[1][0], 0);
    ASSERT_EQ(state[1][1], 1);
    ASSERT_EQ(state[1][2], 2);
    ASSERT_EQ(state[1][3], 3);
    ASSERT_EQ(state[2].size(), 4);
    ASSERT_EQ(state[2][0], 0);
    ASSERT_EQ(state[2][1], 1);
    ASSERT_EQ(state[2][2], 2);
    ASSERT_EQ(state[2][3], 3);
    ASSERT_EQ(state[3].size(), 4);
    ASSERT_EQ(state[3][0], 0);
    ASSERT_EQ(state[3][1], 1);
    ASSERT_EQ(state[3][2], 2);
    ASSERT_EQ(state[3][3], 3);
}
