/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * /
*                ____  ___  _______________   ________    _______            *
*               / __ )/   |/_  __/_  __/   | / ____/ /   /  _/   |           *
*              / __  / /| | / /   / / / /| |/ / __/ /    / // /| |           *
*             / /_/ / ___ |/ /   / / / ___ / /_/ / /____/ // ___ |           *
*            /_____/_/  |_/_/   /_/ /_/  |_\____/_____/___/_/  |_|           *
*                     _   _____ _    _____    __    ______                   *
*                    / | / /   | |  / /   |  / /   / ____/                   *
*                   /  |/ / /| | | / / /| | / /   / __/                      *
*                  / /|  / ___ | |/ / ___ |/ /___/ /___                      *
*                 /_/ |_/_/  |_|___/_/  |_/_____/_____/                      *
*                                                                            *
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
// Developed by Federico Panarotto
// Current Version: 1.3
// GIOCO GRAFICO DI BATTAGLIA NAVALE SU TERMINALE

#include "headers/library_declaration.h"

int main() {
    #if !ENABLE_DEBUG__
        srand(time(NULL));
    #endif

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    checkTerminalHasColors();
    keypad(stdscr, true);

    int center_win = (getmaxx(stdscr)-X_DIM_TERMINALE)/2;
    WINDOW *terminale = newwin(Y_DIM_TERMINALE, X_DIM_TERMINALE, 0, center_win);
    WINDOW *titolo = newwin(4, X_DIM_TERMINALE-2, 1, center_win+1);
    WINDOW *gioco = newwin(12, X_DIM_TERMINALE-2, getmaxy(titolo)+1, center_win+1);
    WINDOW *output = newwin(6, X_DIM_TERMINALE-2, getmaxy(titolo)+getmaxy(gioco)+1, center_win+1);
    WINDOW *input = newwin(4, X_DIM_TERMINALE-2, getmaxy(titolo)+getmaxy(gioco)+getmaxy(output)+1, center_win+1);

    bool gioca_ancora = false;
    visualizzaMenuGiocoInizio(terminale);

    do {
        AreaGioco areaGioco;
        box(terminale, 0, 0);

        wprintcentertext(titolo, 1, "BATTAGLIA NAVALE");
        wprintcentertext(titolo, 2, "Created by Federico Panarotto");
        areaGioco.outputPunteggio(output, 1, 1);
        areaGioco.outputSparo(output, 2, 1);

        #if ENABLE_DEBUG__
            wattron(titolo, COLOR_PAIR(14));
            mvwprintw(titolo, 1, 1, "DEBUG MODE");
            wattroff(titolo, COLOR_PAIR(14));
        #endif

        refresh();
        wrefresh(terminale);
        wrefresh(titolo);
        wrefresh(gioco);
        wrefresh(output);
        wrefresh(input);

        areaGioco.creaAreaGioco();
        areaGioco.generaPosizioniNavi();

        bool punteggio_raggiunto = false;
        int x, y;

        for(int i = 0; i < COLPI && !areaGioco.gioco_terminato; i++) {
            areaGioco.visualizzaAreaGioco(gioco);
            areaGioco.inserisciCoordinate(input, x, y);
            areaGioco.controlloCoordinate(output, x, y);

            if(areaGioco.getPunteggio() >= MAX_PUNTEGGIO) {
                wclear(input);
                string output_text = "HAI RAGGIUNTO IL PUNTEGGIO DI " + to_string(MAX_PUNTEGGIO);
                mvwprintw(input, 0, 1, output_text.c_str());
                mvwprintw(input, 1, 1, "COMPLIMENTI HAI VINTO!");
                punteggio_raggiunto = true;
                areaGioco.gioco_terminato = true;
            }   
        }

        if(!punteggio_raggiunto) {
            wclear(input);
            string output_text = "NON SEI RIUSCITO A OTTENERE " + to_string(MAX_PUNTEGGIO) + " PUNTI";
            mvwprintw(input, 0, 1, output_text.c_str());
            mvwprintw(input, 1, 1, "MI DISPIACE HAI PERSO!");
        }

        mvwprintw(input, 2, 1, "Premi un tasto per terminare il gioco...");
        areaGioco.visualizzaPosizioniNavi();
        areaGioco.visualizzaAreaGioco(gioco);

        refresh();
        wrefresh(terminale);
        wrefresh(titolo);
        wrefresh(gioco);
        wrefresh(output);
        wrefresh(input);

        getch();
        visualizzaMenuGiocoFine(terminale, gioca_ancora, areaGioco.getPunteggio());

    } while(gioca_ancora);

    endwin();
}