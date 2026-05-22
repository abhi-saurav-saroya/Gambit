#pragma once
#include <vector>
#include <string>

class Board {
    public:
        Board();
        const std::vector<std::vector<std::string>>& getGrid() const;
    
    private:
        std::vector<std::vector<std::string>> grid;
};