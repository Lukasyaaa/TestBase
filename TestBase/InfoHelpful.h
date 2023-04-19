#pragma once

enum Color {
    None = -1, Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
    LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

enum Buttons {
    UP_ARROW = 72, DOWN_ARROW = 80, LEFT_ARROW = 75, RIGHT_ARROW = 77, ESC = 27, ENTER = 13
};

enum class HORIZONTAL_POSITION {
    LEFT, CENTER, RIGHT
};

enum class VERTICAL_POSITION {
    TOP, CENTER, BOTTOM
};

enum class ALIGNMENT {
    LEFT, CENTER, RIGHT
};

enum class ACTION {
    PLUS, DIFF, MULT, DEGREE
};