#include "../headers/library_declaration.h"

void checkTerminalHasColors() {
    if(has_colors() == false) {
        endwin();
        exit(1);
    } else {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
        init_pair(10, COLOR_WHITE, COLOR_RED);
        init_pair(11, COLOR_WHITE, COLOR_GREEN);
        init_pair(12, COLOR_BLACK, COLOR_YELLOW);
        init_pair(13, COLOR_WHITE, COLOR_BLUE);
        init_pair(14, COLOR_WHITE, COLOR_CYAN);
    }
}

void wfillAllBckg(WINDOW *win, int val) {
    wattron(win, COLOR_PAIR(val));
    for(int i = 0; i < getmaxy(win); i++) {
        for(int j = 0; j < getmaxx(win); j++) {
            wprintw(win, " ");
        }
    }
    wattroff(win, COLOR_PAIR(val));
}

void wprintcentertext(WINDOW *win, int y, std::string text) {
    int space = (getmaxx(win)-text.length())/2;
    mvwprintw(win, y, space, text.c_str());
}

void wfillwithchar(WINDOW *win, int y, int start_x, const char *c) {
    for(int i = start_x; i < getmaxx(win)-1; i++) {
        mvwprintw(win, y, i, c);
    }
}

void wfillwithcharX(WINDOW *win, int y, int start_x, int end_x, char c) {
    for(int i = start_x; i < end_x; i++) {
        mvwaddch(win, y, i, c);
    }
}

void wprinttextfillingline(WINDOW *win, int y, int x, int x_max, string text) {
    mvwprintw(win, y, x, text.c_str());
    for(int i = 0; i < x_max-text.length(); i++) {
        wprintw(win, " ");
    }
}

bool checkIfIsNumber(string value) {
    for(int i = 0; i < value.length(); i++) {
        bool char_is_number = false;
        for(int j = 48; j < 58 && !char_is_number; j++) {
            if(value[i] == (char)j) {
                char_is_number = true;
            }
        }
        if(!char_is_number) {
            return false;
        }
    }
    return true;
}

bool checkIfIsValidChar(char value) {
    for(int i = 65; i < 75; i++) {
        if(value == (char)i) {
            return true;
        }
    }
    return false;
}