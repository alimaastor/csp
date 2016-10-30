
#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

// A CspProblem represents a particular set of constrains that should not be
// violated. It also detects if a solution has been found by checking the state.
template <class IdType, class DataType>
class CspProblem {
public:
    using CspState = std::unordered_map<IdType, std::vector<DataType>>;
    using CspConstrain = std::function<bool (const CspState&)>;

    friend class CspProblemUnitTest;

    CspProblem() :
        m_constrains()
    {}

    // We want to be sure we don't copy the problem but pass it by reference.
    CspProblem(const CspProblem<IdType, DataType>& other) = delete;
    CspProblem& operator=(const CspProblem<IdType, DataType>& other) = delete;

    void AddConstrain(const CspConstrain& constrain)
    {
        m_constrains.push_back(constrain);
    }

    // Checks that a solution can still be found because the constrains are not violated.
    bool IsConsistent(const CspState& state) const
    {
        return std::all_of(m_constrains.cbegin(), m_constrains.cend(),
                [state](const CspConstrain& constrain)->bool{
                     return constrain(state);
                });
    }

    bool IsSolution(const CspState& state) const
    {
        for (auto s : state)
        {
            if (s.second.size() != 1)
            {
                return false;
            }
        }
        return true;
    }

protected:
    std::vector<CspConstrain> m_constrains;
};

