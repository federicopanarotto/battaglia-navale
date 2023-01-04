#include "../headers/library_declaration.h"

void printMenu(WINDOW *win, int y, vector<string> list, int &selected) {
    for(int i = 0; i < list.size(); i++) {
        if(i == selected) {
            wattron(win, A_REVERSE);
        }
        wprinttextfillingline(win, y+i, 2, getmaxx(win)-4, list[i]);
        wattroff(win, A_REVERSE);
    }
}

void useMenu(WINDOW *win, vector<string> list, int &choice, int &selected) {
    choice = wgetch(win);
    switch(choice) {
        case KEY_UP:
            selected--;
            if(selected == -1) {
                selected = 0;
            }
            break;
        case KEY_DOWN:
            selected++;
            if(selected == list.size()) {
                selected = list.size() -1;
            }
            break;
        default:
            break;
    }
}

void visualizzaMenuGiocoInizio(WINDOW *terminale) {
    wclear(terminale);
    WINDOW *menu = newwin(9, 35, (Y_DIM_TERMINALE-13)/2, X_CENTER+(getmaxx(terminale)-35)/2);
    keypad(menu, true);
    box(menu, 0, 0);
    box(terminale, 0, 0);

    wprintcentertext(menu, 2, "BATTAGLIA NAVALE");
    wprintcentertext(menu, 3, "Created by Federico Panarotto");
    wfillwithcharX(menu, 5, 2, getmaxx(menu)-2, '~');

    refresh();
    wrefresh(terminale);
    wrefresh(menu);

    bool start_game;
    int choice;
    int selected = 0;
    bool continua_selezione = true;
    vector<string> options = {"Gioca!", "Esci"};

    while(continua_selezione) {
        printMenu(menu, 6, options, selected);
        useMenu(menu, options, choice, selected);
        if(choice == 10) {
            switch(selected) {
                case 0:
                    start_game = true;
                    break;
                case 1:
                    start_game = false;
                    break;
            }
            continua_selezione = false;
        }
    }

    if(!start_game) {
        exit(0);
    }

    wclear(menu);
    refresh();
    wrefresh(menu);
}

void visualizzaMenuGiocoFine(WINDOW *terminale, bool &gioca_ancora, int punteggio) {
    wclear(terminale);
    WINDOW *menu = newwin(9, 35, (Y_DIM_TERMINALE-13)/2, X_CENTER+(getmaxx(terminale)-35)/2);
    keypad(menu, true);
    box(menu, 0, 0);
    box(terminale, 0, 0);

    string output_punteggio; 
    if(punteggio >= MAX_PUNTEGGIO) {
        wattron(menu, COLOR_PAIR(11));
        output_punteggio = "HAI VINTO : PUNTEGGIO " + to_string(punteggio);
        wprintcentertext(menu, 2, output_punteggio);
        wattroff(menu, COLOR_PAIR(11));
    } else {
        wattron(menu, COLOR_PAIR(10));
        output_punteggio = "HAI PERSO : PUNTEGGIO " + to_string(punteggio);
        wprintcentertext(menu, 2, output_punteggio);
        wattroff(menu, COLOR_PAIR(10));
    }
    wfillwithcharX(menu, 5, 2, getmaxx(menu)-2, '~');

    refresh();
    wrefresh(terminale);
    wrefresh(menu);

    int choice;
    int selected = 0;
    bool start_game;
    bool continua_selezione = true;
    vector<string> options = {"Gioca ancora", "Esci"};

    while(continua_selezione) {
        printMenu(menu, 6, options, selected);
        useMenu(menu, options, choice, selected);

        if(choice == 10) {
            switch(selected) {
                case 0:
                    gioca_ancora = true;
                    break;
                case 1:
                    gioca_ancora = false;
                    break;
            }
            continua_selezione = false;
        }
    }

    refresh();
    wrefresh(terminale);
    wrefresh(menu);
}