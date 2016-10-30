
#pragma once

#include <unordered_map>
#include <vector>

template <class IdType, class DataType>
class CspState : public std::unordered_map<IdType, std::vector<DataType>>
{
    
};
