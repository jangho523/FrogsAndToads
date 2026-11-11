#include "raylib_controller.hpp"
#include "board_layout.hpp"
#include "raylib.h"

namespace FrogToad {
	void RaylibController::handleInput(BoardModel& model) {

		static_assert(BoardModel::BoardSize <= 9,
			"Single-character commands support at most nine board cells.");

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (auto cell = BoardLayout::cellAt(GetMousePosition()))
			{
				model.tryMove(*cell);
			}
		}

		if (IsKeyPressed(KEY_R))
		{
			model.reset();
			return;
		}

		for (int i = 0; i < BoardModel::BoardSize; i++)
		{
			if (IsKeyPressed(KEY_ONE + i))
			{
				model.tryMove(i);
				break;
			}
		}
	}
}
