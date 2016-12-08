
#include "CspProblem.h"

class NQueensCspProblem
{
public:
    using Problem = CspProblem<std::size_t, std::size_t>;
    using State = Problem::CspState;
    using ArcQueue = Problem::CspArcQueue;
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

    State GetSolution()
    {
        auto state = GetInitialState();
        return RecursiveBacktracking(state);
    }

protected:
    std::size_t GetNextVarId(const State& state)
    {
        return m_problem.GetMinRemainingValuesId(state);
    }

    State ArcConsistency(State& state)
    {
        ArcQueue queue = GetAllArcs();

        while (queue.size() != 0)
        {
            auto arc = queue.pop_front();
            auto xi = arc.first;
            auto xj = arc.second;
            if (RemoveInconsistentValues(state, xi, xj))
            {
                for (std::size_t i = 0; i < m_boardSize; ++i)
                {
                    if (xi != i)
                    {
                        queue.push_back(std::make_pair(i, arc.first));
                    }
                }
            }
        }
        return state;
    }

    bool RemoveInconsistentValues(const State& state, std::size_t xi, std::size_t xj)
    {
        bool removed = false;
        for (auto value1 : state[xi])
        {
            bool allowed = false;
            for (auto value2 : state[xj])
            {
                testState = state;
                testState[xi] = value1;
                testState[xj] = value2;
                if (IsConsistent(testState))
                {
                    allowed = true;
                    break;
                }
            }
            if (!allowed)
            {

            }
        }
        return removed;
    }

    State RecursiveBacktracking(State& state)
    {
        if (m_problem.IsSolution(state))
        {
            return state;
        }

        auto varId = GetNextVarId(state);
        for (const auto& value : state[varId])
        {
            auto newState = state;
            newState[varId] = {value};
            if (m_problem.IsConsistent(newState))
            {
                auto solution = RecursiveBacktracking(newState);
                if (m_problem.IsSolution(solution))
                {
                    return solution;
                }
            }
        }

        return state;
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

    ArcQueue GetAllArcs()
    {
        ArcQueue queue;
        for (std::size_t i = 0; i < m_boardSize; ++i)
        {
            for (std::size_t j = 0; j < m_boardSize; ++j)
            {
                if (i != j)
                {
                    queue.push_back(std::make_pair(i, j));
                }
            }
        }
        return queue;
    }

    void SetValueToVar(State& state, const std::size_t index, const std::size_t value) const
    {
        std::vector<std::size_t>& values = state[index];
        if (values.size() == 0)
        {
            throw std::runtime_error("No values left");
        }
        if (std::all_of(values.cbegin(), values.cend(), [value](const std::size_t v){ return v != value; }))
        {
            throw std::runtime_error("Value not in state");
        }
        state[index] = {value};
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
