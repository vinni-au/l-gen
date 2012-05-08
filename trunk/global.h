#ifndef GLOBAL_H
#define GLOBAL_H

#if defined(DEBUG) | defined(DIAGNOSTIC)
    #define NOW QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz")
    #include <QDebug>
    #include <QDateTime>
#endif

#endif // GLOBAL_H
