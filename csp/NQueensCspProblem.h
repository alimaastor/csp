
#include "CspProblem.h"

class NQueensCspProblem
{
public:
    using Problem = CspProblem<std::size_t, std::size_t>;
    using State = Problem::CspState;
    friend class NQueensCspProblemTester;

    NQueensCspProblem(const std::size_t boardSize) :
        m_problem(),
        m_boardSize(boardSize)
    {
        // Define the N-Queens problem in terms of constrains.
        // 1) If a queen has no positions left, the problem cannot be solved:
        m_problem.AddConstrain([](const State& state){
            for (auto pair : state)
            {
                if (pair.second.size() == 0)
                {
                    return false;
                }
            }
            return true;
        });
        // 2) If two queens are threatening each other (only one position left for
        // each), the problem cannot be solved:
        m_problem.AddConstrain([this](const State& state){
            for (std::size_t i = 0; i < m_boardSize; ++i)
            {
                const auto& values1 = state.find(i)->second;
                if (values1.size() != 1)
                {
                    continue;
                }
                for (std::size_t j = i + 1; j < m_boardSize; ++j)
                {
                    const auto& values2 = state.find(j)->second;
                    if (values2.size() != 1)
                    {
                        continue;
                    }
                    const auto value1 = values1[0];
                    const auto value2 = values2[0];
                    if ((value1 == value2) || (abs(value1 - value2) == abs(i - j)))
                    {
                        return false;
                    }
                }
            }
            return true;
        });
    }

protected:
    std::size_t GetNextVarId(const State& state)
    {
        return m_problem.GetMinRemainingValuesId(state);
    }

private:

    State GetInitialState() const
    {
        State state;
        for (std::size_t i = 0; i < m_boardSize; ++i)
        {
            for (std::size_t j = 0; j < m_boardSize; ++j)
            {
                state[j].push_back(i);
            }
        }
        return state;
    }

    void RemoveValueFromVar(State& state, const std::size_t index, const std::size_t value) const
    {
        std::vector<std::size_t>& values = state[index];
        const auto sBefore = values.size();
        values.erase(std::remove(values.begin(), values.end(), value), values.end());
        const auto sAfter = values.size();
        if (sBefore == sAfter)
        {
            throw std::runtime_error("Could not find value to remove");
        }
    }

    Problem     m_problem;
    std::size_t m_boardSize;
};
