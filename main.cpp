/* Begin of file: main.cpp */

/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.hpp"

#ifdef Q_WS_X11
#include <signal.h>
#include <QMessageBox>

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    QMessageBox::critical(0, "Критическая ошибка", "В программе произошла критическая ошибка!"
                                                   "<br>Программа будет перезапущена");
    //TODO перезапустить программу
    exit(0);
}

#else
#ifdef Q_WS_WIN
//TODO Написать поимку memory access violation для Windows
#endif
#endif


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#ifdef Q_WS_X11
    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
#else
#ifdef Q_WS_WIN
#endif
#endif

    return a.exec();;
}

/* End of file: main.cpp */
