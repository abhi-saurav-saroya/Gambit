#pragma once

#include <vector>
#include <utility>
#include <string>

namespace King {
    std::vector<std::pair<int,int>> getLegalMoves(
        const std::vector<std::vector<std::string>>& grid,
        int row,
        int col
    );
}