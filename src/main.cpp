#include <ncurses.h>
#include <unistd.h>
#include <iomanip>
#include <sys/ioctl.h>

#include "cpu.h"
#include "window.h"
#include "init.h"
#include "utils.h"
#include "runtime.h"

int main()
{

    if (!init()) // ncurses initialization, fails if terminal not supported
    {
        return EXIT_FAILURE;
    }

    struct winsize w;
    Cpu cpu;
    bool running = true;

    ioctl(0, TIOCGWINSZ, &w);
    const int T_ROWS = w.ws_row;
    const int T_COLS = w.ws_col;

    WindowWrap disp(T_ROWS / 2, T_COLS / 2, 0, 0);
    WindowWrap disp_2(T_ROWS / 2, T_COLS / 2, 0, T_COLS / 2);
    WindowWrap menu((T_ROWS / 2) + 1, T_COLS, T_ROWS / 2, 0);

    refresh();

    box(disp_2.getWin(), 0, 0);

    wrefresh(disp.getWin());
    wrefresh(disp_2.getWin());
    wrefresh(menu.getWin());

    // display cpu model above graph
    displayElement(disp, 2, 2, cpu.getModelName(), flag::standard, flag::none);

    while (running)
    {
        updateWindowOne(disp, cpu); // window that contains cpu utiliation

        displaySystemProcesses(menu);

        refresh();
        wrefresh(menu.getWin());
        wrefresh(disp_2.getWin());
        wrefresh(disp.getWin());
        sleep(1);
    }

    // deallocates and ends ncurses
    endwin();

    return 0;
}
