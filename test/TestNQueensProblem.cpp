
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

    NQueensCspProblem::ArcQueue GetAllArcs()
    {
        return m_problemPtr->GetAllArcs();
    }

    void SetValueToVar(NQueensCspProblem::State& state, const std::size_t index, const std::size_t value)
    {
        m_problemPtr->SetValueToVar(state, index, value);
    }

    void RemoveValueFromVar(NQueensCspProblem::State& state, const std::size_t index, const std::size_t value)
    {
        m_problemPtr->RemoveValueFromVar(state, index, value);
    }

    bool IsConsistent(const NQueensCspProblem::State& state)
    {
        return m_problemPtr->m_problem.IsConsistent(state);
    }

    bool IsSolution(const NQueensCspProblem::State& state)
    {
        return m_problemPtr->m_problem.IsSolution(state);
    }

private:
    std::shared_ptr<NQueensCspProblem> m_problemPtr;
};

TEST(NQueensProblemTest, SetValue)
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

    tester.SetValueToVar(state, 0, 2);

    ASSERT_EQ(state[0].size(), 1);
    ASSERT_EQ(state[0][0], 2);
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

    ASSERT_THROW(tester.SetValueToVar(state, 0, 1), std::runtime_error);
}

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

    ASSERT_THROW(tester.RemoveValueFromVar(state, 0, 2), std::runtime_error);
}

TEST(NQueensProblemTest, IsConsistent)
{
    auto problemPtr = std::make_shared<NQueensCspProblem>(4);
    auto tester = NQueensCspProblemTester(problemPtr);

    {
        NQueensCspProblem::State state = {
            {0, {1, 2}},
            {1, {1, 2}},
            {2, {1, 2}},
            {3, {1, 2}}
        };

        ASSERT_TRUE(tester.IsConsistent(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {1}},
            {2, {1, 2}},
            {3, {1, 2}}
        };

        ASSERT_FALSE(tester.IsConsistent(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {2}},
            {2, {1, 2}},
            {3, {1, 2}}
        };

        ASSERT_FALSE(tester.IsConsistent(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {}},
            {1, {2}},
            {2, {1, 2}},
            {3, {1, 2}}
        };

        ASSERT_FALSE(tester.IsConsistent(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {3}},
            {2, {1, 2}},
            {3, {1, 2}}
        };

        ASSERT_TRUE(tester.IsConsistent(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {3}},
            {2, {1, 2}},
            {3, {4}}
        };

        ASSERT_FALSE(tester.IsConsistent(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {3}},
            {2, {0}},
            {3, {2}}
        };

        ASSERT_TRUE(tester.IsConsistent(state));
    }
}

TEST(NQueensProblemTest, IsSolution)
{
    auto problemPtr = std::make_shared<NQueensCspProblem>(4);
    auto tester = NQueensCspProblemTester(problemPtr);

    {
        NQueensCspProblem::State state = {
            {0, {1, 2}},
            {1, {1, 2}},
            {2, {1, 2}},
            {3, {1, 2}}
        };

        ASSERT_FALSE(tester.IsSolution(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {1}},
            {2, {1}},
            {3, {1}}
        };

        ASSERT_FALSE(tester.IsSolution(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {3}},
            {2, {0}},
            {3, {1, 2}}
        };

        ASSERT_FALSE(tester.IsSolution(state));
    }
    {
        NQueensCspProblem::State state = {
            {0, {1}},
            {1, {3}},
            {2, {0}},
            {3, {2}}
        };

        ASSERT_TRUE(tester.IsSolution(state));
    }
}
TEST(NQueensProblemTest, GetAllArcs)
{
    auto problemPtr = std::make_shared<NQueensCspProblem>(4);
    auto tester = NQueensCspProblemTester(problemPtr);
    auto queue = tester.GetAllArcs();

    ASSERT_EQ(queue[ 0].first,  0);
    ASSERT_EQ(queue[ 0].second, 1);
    ASSERT_EQ(queue[ 1].first,  0);
    ASSERT_EQ(queue[ 1].second, 2);
    ASSERT_EQ(queue[ 2].first,  0);
    ASSERT_EQ(queue[ 2].second, 3);
    ASSERT_EQ(queue[ 3].first,  1);
    ASSERT_EQ(queue[ 3].second, 0);
    ASSERT_EQ(queue[ 4].first,  1);
    ASSERT_EQ(queue[ 4].second, 2);
    ASSERT_EQ(queue[ 5].first,  1);
    ASSERT_EQ(queue[ 5].second, 3);
    ASSERT_EQ(queue[ 6].first,  2);
    ASSERT_EQ(queue[ 6].second, 0);
    ASSERT_EQ(queue[ 7].first,  2);
    ASSERT_EQ(queue[ 7].second, 1);
    ASSERT_EQ(queue[ 8].first,  2);
    ASSERT_EQ(queue[ 8].second, 3);
    ASSERT_EQ(queue[ 9].first,  3);
    ASSERT_EQ(queue[ 9].second, 0);
    ASSERT_EQ(queue[10].first,  3);
    ASSERT_EQ(queue[10].second, 1);
    ASSERT_EQ(queue[11].first,  3);
    ASSERT_EQ(queue[11].second, 2);
    ASSERT_EQ(queue.size(), 12);
}
