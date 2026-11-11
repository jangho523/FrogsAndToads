#pragma once
#include "interfaces.hpp"

namespace FrogToad {
    /** @brief Presents a colored board using ANSI terminal escape sequences. */
    class AnsiView : public IView {
    public:
        /** @brief Clear the terminal and hide its cursor; select UTF-8 output on Windows. */
        AnsiView();
        /** @brief Reset terminal styles and show the cursor. */
        ~AnsiView();

        /** @brief Redraw the board, numbered positions, and solved status in place. */
        void draw(const BoardModel& model) override;

    private:
        /** @brief Draw a board border with one segment per cell. */
        static void drawBorder(const char* left, const char* separator, const char* right);

        // ANSI Escape Code Helpers
        // Returning const char* avoids constructing a std::string on each call.
        static const char* resetStyles() { return "\x1b[0m"; }
        static const char* clearScreen() { return "\x1b[2J"; }
        static const char* hideCursor()  { return "\x1b[?25l"; }
        static const char* showCursor()  { return "\x1b[?25h"; }
        static const char* eraseAfter()  { return "\x1b[0J"; }
        static const char* cursorHome()  { return "\x1b[H"; }

        // Fixed 256-colour palette entries keep text readable on the black background.
        static const char* background() { return "\x1b[48;5;16m"; }
        static const char* white()      { return "\x1b[38;5;255m"; }
        static const char* grey()       { return "\x1b[38;5;250m"; }
        static const char* brown()      { return "\x1b[38;5;180m"; }
        static const char* green()      { return "\x1b[38;5;82m"; }
        static const char* blue()       { return "\x1b[38;5;33m"; }
        // Available for the student loss-display exercise.
        static const char* red()        { return "\x1b[38;5;196m"; }
    };
}
