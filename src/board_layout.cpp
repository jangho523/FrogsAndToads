#include "board_layout.hpp"
#include "board_model.hpp"
#include <cassert> // assert() in cellRect()

namespace FrogToad {
    Rectangle BoardLayout::board() {
        return {Left,Top,CellSize * BoardModel::BoardSize, CellSize}; // Replace with the rectangle covering all cells.
    }

    Rectangle BoardLayout::cellRect(int index) {
        // Assert that the index is valid:
        assert(index >= 0 && index < BoardModel::BoardSize);

        return { Left + CellSize * index,Top,CellSize, CellSize };
    }

    std::optional<int> BoardLayout::cellAt(Vector2 point) {
        
        if (point.y >= Top && point.y < Top + CellSize)
        {
            for (int i = 0; i < BoardModel::BoardSize;i++)
            {
                if (point.x >= Left + CellSize * i && point.x < Left + CellSize + CellSize * i)
                {
                    return i;
                }
            }
        }

        // Return nullopt only when the point is off the board.
        return std::nullopt;
    }
}
