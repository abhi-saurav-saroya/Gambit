#include "pieces/bishop.hpp"
#include "pieces/move_gen.hpp"

std::vector<std::pair<int,int>> Bishop::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    const std::string& piece = grid[row][col];

    if (piece != "WhiteBishop" && piece != "BlackBishop") {
        return {};
    }

    // bishop directions
    static const Moves::Offsets dirs = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    return Moves::sliding(grid, row, col, dirs);
}
