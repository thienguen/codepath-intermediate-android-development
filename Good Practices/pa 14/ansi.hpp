/// This file provides simple means of manipulating ANSI/VT100 terminals.
///
/// @file ansi.h
/// @version 2018-04-08 Original
/// @version 2020-03-02 Refactored--implemented as stream manipulators.
/// @author Kevin Mess
/// @sa https://en.wikipedia.org/wiki/ANSI_escape_code

#ifndef ANSI_H_
#define ANSI_H_

#include <iostream>

namespace ansi {
enum attr_t {
    RESET          = 0,
    BOLD_ON        = 1,
    DIM_ON         = 2,
    UNDERLINED_ON  = 4,
    BLINK_ON       = 5,
    REVERSE_ON     = 7,
    HIDDEN_ON      = 8,
    BOLD_OFF       = 21,
    DIM_OFF        = 22,
    UNDERLINED_OFF = 24,
    BLINK_OFF      = 25,
    REVERSE_OFF    = 27,
    HIDDEN_OFF     = 28,
    FG_BLACK       = 30,
    FG_RED         = 31,
    FG_GREEN       = 32,
    FG_YELLOW      = 33,
    FG_BLUE        = 34,
    FG_MAGENTA     = 35,
    FG_CYAN        = 36,
    FG_LT_GRAY     = 37,
    FG_DEFAULT     = 39,
    BG_BLACK       = 40,
    BG_RED         = 41,
    BG_GREEN       = 42,
    BG_YELLOW      = 43,
    BG_BLUE        = 44,
    BG_MAGENTA     = 45,
    BG_CYAN        = 46,
    BG_LT_GRAY     = 47,
    BG_DEFAULT     = 49,
    FG_DK_GRAY     = 90,
    FG_LT_RED      = 91,
    FG_LT_GREEN    = 92,
    FG_LT_YELLOW   = 93,
    FG_LT_BLUE     = 94,
    FG_LT_MAGENTA  = 95,
    FG_LT_CYAN     = 96,
    FG_WHITE       = 97,
    BG_DK_GRAY     = 100,
    BG_LT_RED      = 101,
    BG_LT_GREEN    = 102,
    BG_LT_YELLOW   = 103,
    BG_LT_BLUE     = 104,
    BG_LT_MAGENTA  = 105,
    BG_LT_CYAN     = 106,
    BG_WHITE       = 107
};

static const char ESC[] = "\033["; ///< Escape sequence precedes color code

// prototypes
void demo();

// definitions
inline std::ostream& set_attr(ansi::attr_t  attr, std::ostream& output = std::cout) {
    return output << ESC << attr << 'm';
}

inline std::ostream& reset(std::ostream& os) { return os << ESC << RESET << 'm'; }
inline std::ostream& bold(std::ostream& os) { return os << ESC << BOLD_ON << 'm'; }
inline std::ostream& dim(std::ostream& os) { return os << ESC << DIM_ON << 'm'; }
inline std::ostream& underlined(std::ostream& os) { return os << ESC << UNDERLINED_ON << 'm'; }
inline std::ostream& blink(std::ostream& os) { return os << ESC << BLINK_ON << 'm'; }
inline std::ostream& reverse(std::ostream& os) { return os << ESC << REVERSE_ON << 'm'; }
inline std::ostream& hidden(std::ostream& os) { return os << ESC << HIDDEN_ON << 'm'; }
inline std::ostream& bold_off(std::ostream& os) { return os << ESC << BOLD_OFF << 'm'; }
inline std::ostream& dim_off(std::ostream& os) { return os << ESC << DIM_OFF << 'm'; }
inline std::ostream& underlined_off(std::ostream& os) { return os << ESC << UNDERLINED_OFF << 'm'; }
inline std::ostream& blink_off(std::ostream& os) { return os << ESC << BLINK_OFF << 'm'; }
inline std::ostream& reverse_off(std::ostream& os) { return os << ESC << REVERSE_OFF << 'm'; }
inline std::ostream& hidden_off(std::ostream& os) { return os << ESC << HIDDEN_OFF << 'm'; }
inline std::ostream& black(std::ostream& os) { return os << ESC << FG_BLACK << 'm'; }
inline std::ostream& red(std::ostream& os) { return os << ESC << FG_RED << 'm'; }
inline std::ostream& green(std::ostream& os) { return os << ESC << FG_GREEN << 'm'; }
inline std::ostream& yellow(std::ostream& os) { return os << ESC << FG_YELLOW << 'm'; }
inline std::ostream& blue(std::ostream& os) { return os << ESC << FG_BLUE << 'm'; }
inline std::ostream& magenta(std::ostream& os) { return os << ESC << FG_MAGENTA << 'm'; }
inline std::ostream& cyan(std::ostream& os) { return os << ESC << FG_CYAN << 'm'; }
inline std::ostream& lt_gray(std::ostream& os) { return os << ESC << FG_LT_GRAY << 'm'; }
inline std::ostream& fg_default(std::ostream& os) { return os << ESC << FG_DEFAULT << 'm'; }
inline std::ostream& bg_black(std::ostream& os) { return os << ESC << BG_BLACK << 'm'; }
inline std::ostream& bg_red(std::ostream& os) { return os << ESC << BG_RED << 'm'; }
inline std::ostream& bg_green(std::ostream& os) { return os << ESC << BG_GREEN << 'm'; }
inline std::ostream& bg_yellow(std::ostream& os) { return os << ESC << BG_YELLOW << 'm'; }
inline std::ostream& bg_blue(std::ostream& os) { return os << ESC << BG_BLUE << 'm'; }
inline std::ostream& bg_magenta(std::ostream& os) { return os << ESC << BG_MAGENTA << 'm'; }
inline std::ostream& bg_cyan(std::ostream& os) { return os << ESC << BG_CYAN << 'm'; }
inline std::ostream& bg_lt_gray(std::ostream& os) { return os << ESC << BG_LT_GRAY << 'm'; }
inline std::ostream& bg_default(std::ostream& os) { return os << ESC << BG_DEFAULT << 'm'; }
inline std::ostream& dk_gray(std::ostream& os) { return os << ESC << FG_DK_GRAY << 'm'; }
inline std::ostream& lt_red(std::ostream& os) { return os << ESC << FG_LT_RED << 'm'; }
inline std::ostream& lt_green(std::ostream& os) { return os << ESC << FG_LT_GREEN << 'm'; }
inline std::ostream& lt_yellow(std::ostream& os) { return os << ESC << FG_LT_YELLOW << 'm'; }
inline std::ostream& lt_blue(std::ostream& os) { return os << ESC << FG_LT_BLUE << 'm'; }
inline std::ostream& lt_magenta(std::ostream& os) { return os << ESC << FG_LT_MAGENTA << 'm'; }
inline std::ostream& lt_cyan(std::ostream& os) { return os << ESC << FG_LT_CYAN << 'm'; }
inline std::ostream& white(std::ostream& os) { return os << ESC << FG_WHITE << 'm'; }
inline std::ostream& bg_dk_gray(std::ostream& os) { return os << ESC << BG_DK_GRAY << 'm'; }
inline std::ostream& bg_lt_red(std::ostream& os) { return os << ESC << BG_LT_RED << 'm'; }
inline std::ostream& bg_lt_green(std::ostream& os) { return os << ESC << BG_LT_GREEN << 'm'; }
inline std::ostream& bg_lt_yellow(std::ostream& os) { return os << ESC << BG_LT_YELLOW << 'm'; }
inline std::ostream& bg_lt_blue(std::ostream& os) { return os << ESC << BG_LT_BLUE << 'm'; }
inline std::ostream& bg_lt_magenta(std::ostream& os) { return os << ESC << BG_LT_MAGENTA << 'm'; }
inline std::ostream& bg_lt_cyan(std::ostream& os) { return os << ESC << BG_LT_CYAN << 'm'; }
inline std::ostream& bg_white(std::ostream& os) { return os << ESC << BG_WHITE << 'm'; }

void demo() {
    const attr_t fg_colors[] = {
        FG_BLACK,    FG_RED,       FG_GREEN,     FG_YELLOW,    FG_BLUE,
        FG_MAGENTA,  FG_CYAN,      FG_LT_GRAY,   FG_DEFAULT,   FG_DK_GRAY,
        FG_LT_RED,   FG_LT_GREEN,  FG_LT_YELLOW, FG_LT_BLUE,   FG_LT_MAGENTA,
        FG_LT_CYAN,  FG_WHITE
    };
    const attr_t attr[] = {
        BOLD_ON, DIM_ON, UNDERLINED_ON, BLINK_ON, REVERSE_ON
    };

    std::cout << "You can print using output manipulators like ";
    std::cout << ansi::red   << "RED "
              << ansi::green << "GREEN "
              << ansi::blue  << "BLUE"
              << ansi::reset << '\n';

    std::cout << "A variety of configurations are possible:\n";

    for (auto fg : fg_colors) {
        for (auto at : attr) {
            ansi::set_attr(fg, std::cout);
            ansi::set_attr(at);
            std::cout << "   ^[" << at << ';' << fg << "m   ";
            ansi::set_attr(ansi::RESET);
        }

        std::cout << '\n';
    }

    std::cout << std::endl;
}
}  // namespace ansi

#endif  /* ANSI_H_ */

