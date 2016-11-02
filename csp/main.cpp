
#include <NQueensCspProblem.h>

#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
    std::istringstream ss(argv[1]);
    int x;
    if (!(ss >> x))
    {
        std::cerr << "Invalid number " << argv[1] << std::endl;
        return 1;
    }

    NQueensCspProblem problem(x);
    auto solution = problem.GetSolution();
    for (auto pair : solution)
    {
        std::cout << "ID: " << pair.first << "; Value: " << pair.second[0] << std::endl;
    }
    return 0;
}

