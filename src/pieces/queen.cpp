#include "pieces/queen.hpp"
#include "pieces/move_gen.hpp"

std::vector<std::pair<int,int>> Queen::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    const std::string& piece = grid[row][col];

    if (piece != "WhiteQueen" && piece != "BlackQueen") {
        return {};
    }

    // queen directions — rook rays followed by bishop rays
    static const Moves::Offsets dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    return Moves::sliding(grid, row, col, dirs);
}
