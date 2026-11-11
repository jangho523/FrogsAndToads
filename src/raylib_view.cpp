#include "raylib_view.hpp"
#include "board_layout.hpp"

namespace FrogToad {
	RaylibView::RaylibView() {
		frogTexture = LoadTexture("resources/frog.png");
		toadTexture = LoadTexture("resources/toad.png");
		frogHoverTexture = LoadTexture("resources/frog_hover.png");
		toadHoverTexture = LoadTexture("resources/toad_hover.png");

		GenTextureMipmaps(&frogTexture);
		SetTextureFilter(frogTexture, TEXTURE_FILTER_TRILINEAR);
		GenTextureMipmaps(&toadTexture);
		SetTextureFilter(toadTexture, TEXTURE_FILTER_TRILINEAR);
		GenTextureMipmaps(&frogHoverTexture);
		SetTextureFilter(frogHoverTexture, TEXTURE_FILTER_TRILINEAR);
		GenTextureMipmaps(&toadHoverTexture);
		SetTextureFilter(toadHoverTexture, TEXTURE_FILTER_TRILINEAR);
	}

	RaylibView::~RaylibView() {
		UnloadTexture(frogTexture);
		UnloadTexture(toadTexture);
		UnloadTexture(frogHoverTexture);
		UnloadTexture(toadHoverTexture);
	}

	void RaylibView::draw(const BoardModel& model) {
		ClearBackground(RAYWHITE);

		DrawText("Toads & Frogs", 200, 30, 50, BLACK);
		DrawText("Restart: R", 650, 350, 20, BLACK);

		auto cellMouse = BoardLayout::cellAt(GetMousePosition());

		for(int i = 0; i < BoardModel::BoardSize; i++)
		{
			Rectangle cellRect = BoardLayout::cellRect(i);

			// Draw the default frog and toad textures.
			if (model.cellAt(i) == BoardModel::Cell::Frog)
			{
				DrawTexturePro(frogTexture, { 0, 0, (float)frogTexture.width, (float)frogTexture.height }, cellRect, { 0, 0 }, 0.0f, WHITE);
			}
			else if (model.cellAt(i) == BoardModel::Cell::Toad)
			{
				DrawTexturePro(toadTexture, { 0, 0, (float)toadTexture.width, (float)toadTexture.height }, cellRect, { 0, 0 }, 0.0f, WHITE);
			}
			DrawRectangleLinesEx({ cellRect }, 2.f, BLACK);
			
			// Highlight the hovered cell and display its hover texture.
			if (cellMouse == i)
			{
				if (model.cellAt(i) == BoardModel::Cell::Frog)
				{
					DrawTexturePro(frogHoverTexture, { 0, 0, (float)frogHoverTexture.width, (float)frogHoverTexture.height }, cellRect, { 0, 0 }, 0.0f, WHITE);
				}
				else if (model.cellAt(i) == BoardModel::Cell::Toad)
				{
					DrawTexturePro(toadHoverTexture, { 0, 0, (float)toadHoverTexture.width, (float)toadHoverTexture.height }, cellRect, { 0, 0 }, 0.0f, WHITE);
				}
				DrawRectangleLinesEx({ cellRect }, 2.f, RED);
			}
			
			DrawText(TextFormat("%d", i + 1), cellRect.x + cellRect.width / 2 - 4, cellRect.y + cellRect.height + 10, 20, BLACK);
		}

		if (model.state() == BoardModel::GameState::Lost)
		{
			DrawText("You lost! R to restart.", 50, 250, 20, RED);
		}
		else if (model.state() == BoardModel::GameState::Solved)
		{
			DrawText("Solved! R to restart", 50, 250, 20, GOLD);
		}
	}

	int RaylibView::windowW() { return 800; }
	int RaylibView::windowH() { return 400; }
}
