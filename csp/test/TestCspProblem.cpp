
#include "../NQueensCspProblem.h"

#include <gtest/gtest.h>

#include <vector>
#include <memory>

class CspProblemUnitTest
{
public:
    CspProblemUnitTest(const std::shared_ptr<CspProblem<std::size_t, std::size_t>>& problemPtr) :
        m_problemPtr(problemPtr)
    {}

    std::size_t GetNumberConstrains()
    {
        return m_problemPtr->m_constrains.size();
    }

private:
    std::shared_ptr<CspProblem<std::size_t, std::size_t>> m_problemPtr;
};

TEST(CspProblemTest, AddConstrain)
{
    auto problemPtr = std::make_shared<CspProblem<std::size_t, std::size_t>>();
    auto tester = CspProblemUnitTest(problemPtr);
    ASSERT_EQ(0, tester.GetNumberConstrains());
    problemPtr->AddConstrain([](const CspProblem<std::size_t, std::size_t>::CspState& state){return true;});
    ASSERT_EQ(1, tester.GetNumberConstrains());
    problemPtr->AddConstrain([](const CspProblem<std::size_t, std::size_t>::CspState& state){return true;});
    ASSERT_EQ(2, tester.GetNumberConstrains());
}

TEST(CspProblemTest, ValidateConstrains1)
{
    auto problemPtr = std::make_shared<CspProblem<std::size_t, std::size_t>>();
    auto tester = CspProblemUnitTest(problemPtr);
    auto dummyState = CspProblem<std::size_t, std::size_t>::CspState();
    ASSERT_EQ(0, tester.GetNumberConstrains());
    problemPtr->AddConstrain([](const CspProblem<std::size_t, std::size_t>::CspState& state){return true;});
    ASSERT_EQ(1, tester.GetNumberConstrains());
    ASSERT_TRUE(problemPtr->IsConsistent(dummyState));
    problemPtr->AddConstrain([](const CspProblem<std::size_t, std::size_t>::CspState& state){return false;});
    ASSERT_EQ(2, tester.GetNumberConstrains());
    ASSERT_FALSE(problemPtr->IsConsistent(dummyState));
}

TEST(CspProblemTest, ValidateConstrains2)
{
    CspProblem<std::size_t, std::size_t> problem;
    std::size_t size = 2;
    problem.AddConstrain(
        [size](const CspProblem<std::size_t, std::size_t>::CspState& s){
            for (std::size_t i = 0; i < size; ++i)
            {
                // Dummy constrain, returns true if two variables
                // are set to the same value.
                auto it1 = s.find(i);
                if(it1 != s.end() && it1->second.size() == 1)
                {
                    auto value1 = it1->second[0];
                    for (std::size_t j = i + 1; j < size; ++j)
                    {
                        auto it2 = s.find(j);
                        if (it2 != s.end() && it2->second.size() == 1)
                        {
                            auto value2 = it2->second[0];
                            if (value1 == value2)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
    });

    auto state1 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1,2}}, {1,{2}}});
    ASSERT_TRUE(problem.IsConsistent(state1));
    auto state2 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1}}, {1,{2}}});
    ASSERT_TRUE(problem.IsConsistent(state2));
    auto state3 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1}}, {1,{1}}});
    ASSERT_FALSE(problem.IsConsistent(state3));
}

TEST(CspProblemTest, FindSolution)
{
    CspProblem<std::size_t, std::size_t> problem;

    auto state1 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1,2}}, {1,{2}}});
    ASSERT_FALSE(problem.IsSolution(state1));
    auto state2 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1}}, {1,{2}}});
    ASSERT_TRUE(problem.IsSolution(state2));
    auto state3 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1}}, {1,{}}});
    ASSERT_FALSE(problem.IsSolution(state3));
}

TEST(CspProblemTest, GetFirstUnassignedVariable)
{
    CspProblem<std::size_t, std::size_t> problem;

    auto state1 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1,2}}, {1,{2}}});
    ASSERT_EQ(problem.GetFirstUnassignedValueId(state1), 0);
    auto state2 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1}}, {1,{2}}});
    ASSERT_THROW(problem.GetFirstUnassignedValueId(state2), std::runtime_error);
    auto state3 = CspProblem<std::size_t, std::size_t>::CspState({{0,{}}, {1,{2}}});
    ASSERT_THROW(problem.GetFirstUnassignedValueId(state3), std::runtime_error);
}

TEST(CspProblemTest, GetMinRemainingValuesUnassignedVariable)
{
    CspProblem<std::size_t, std::size_t> problem;

    auto state1 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1,2}}, {1,{2}}, {2,{2, 3, 4, 5}}});
    ASSERT_EQ(problem.GetMinRemainingValuesId(state1), 0);
    auto state2 = CspProblem<std::size_t, std::size_t>::CspState({{0,{}}, {1,{2}}, {2,{2, 3, 4}}});
    ASSERT_EQ(problem.GetMinRemainingValuesId(state2), 2);
    auto state3 = CspProblem<std::size_t, std::size_t>::CspState({{0,{}}, {1,{2}}});
    ASSERT_THROW(problem.GetMinRemainingValuesId(state3), std::runtime_error);
}

TEST(CspProblemTest, GetMaxRemainingValuesUnassignedVariable)
{
    CspProblem<std::size_t, std::size_t> problem;

    auto state1 = CspProblem<std::size_t, std::size_t>::CspState({{0,{1,2}}, {1,{2}}, {2,{2, 3, 4, 5}}});
    ASSERT_EQ(problem.GetMaxRemainingValuesId(state1), 2);
    auto state2 = CspProblem<std::size_t, std::size_t>::CspState({{0,{}}, {1,{2}}, {2,{2, 3, 4}}});
    ASSERT_EQ(problem.GetMaxRemainingValuesId(state2), 2);
    auto state3 = CspProblem<std::size_t, std::size_t>::CspState({{0,{}}, {1,{2}}});
    ASSERT_THROW(problem.GetMaxRemainingValuesId(state3), std::runtime_error);
}

