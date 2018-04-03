#include "frmmain.h"
#include <QApplication>
#include <QTextCodec>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if QT_5
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
#endif

  //  QTranslator translator;
  //  translator.load( "msyh.ttc", qApp->applicationDirPath() );
  //  qApp->installTranslator( &translator );

    FrmMain w;

    w.setFont(QFont(appFontName));

    w.show();

    return a.exec();
}
