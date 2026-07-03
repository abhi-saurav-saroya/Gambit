#include "pieces/king.hpp"
#include "pieces/move_gen.hpp"

std::vector<std::pair<int,int>> King::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    const std::string& piece = grid[row][col];

    if (piece != "WhiteKing" && piece != "BlackKing") {
        return {};
    }

    // all 8 king directions
    static const Moves::Offsets offsets = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    return Moves::stepping(grid, row, col, offsets);
}
