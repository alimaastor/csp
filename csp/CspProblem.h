
#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <limits>

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

    IdType GetFirstUnassignedValueId(const CspState& state) const
    {
        for (auto pair : state)
        {
            if (pair.second.size() > 1)
            {
                return pair.first;
            }
        }
        throw std::runtime_error("No unassigned variables left");
        return IdType();
    }

    IdType GetMaxRemainingValuesId(const CspState& state) const
    {
        auto pair = std::max_element(state.begin(), state.end(),
                [](const std::pair<IdType, std::vector<DataType>>& mapEntry1, const std::pair<IdType, std::vector<DataType>>& mapEntry2)->bool{
                    return (mapEntry1.second.size() < mapEntry2.second.size());
                });

        if (pair->second.size() < 2)
        {
            throw std::runtime_error("No unassigned variables left");
        }

        return pair->first;
    }

    IdType GetMinRemainingValuesId(const CspState& state) const
    {
        bool found = false;
        IdType id;
        std::size_t min_size = std::numeric_limits<std::size_t>::max();
        for (auto pair : state)
        {
            auto size = pair.second.size();
            if ((size > 1) && (size < min_size))
            {
                min_size = size;
                id = pair.first;
                found = true;
            }
        }

        if (!found)
        {
            throw std::runtime_error("No unassigned variables left");
        }

        return id;
    }

protected:
    std::vector<CspConstrain> m_constrains;
};

