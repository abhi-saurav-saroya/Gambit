#include "pieces/knight.hpp"
#include "pieces/move_gen.hpp"

std::vector<std::pair<int,int>> Knight::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    const std::string& piece = grid[row][col];

    if (piece != "WhiteKnight" && piece != "BlackKnight") {
        return {};
    }

    // all 8 knight jumps
    static const Moves::Offsets offsets = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    return Moves::stepping(grid, row, col, offsets);
}
