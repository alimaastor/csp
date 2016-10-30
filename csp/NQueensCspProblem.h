
#include "CspProblem.h"

class NQueensCspProblem : public CspProblem<std::size_t, std::size_t>
{
public:
    using State = CspProblem<std::size_t, std::size_t>::CspState;

    NQueensCspProblem() :
        CspProblem<std::size_t, std::size_t>()
    {}
};
