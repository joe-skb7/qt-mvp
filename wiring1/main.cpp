#include <QApplication>
#include <QTextCodec>
#include "wiringform.h"
#include "wiringpresenter.h"

/*!
    Устанавливает текстовые кодеки для кодировки \a codecName.
*/
void initTextCodecs(const char *codecName)
{
    QTextCodec *codec = QTextCodec::codecForName(codecName);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
}

int main(int argc, char *argv[])
{
    initTextCodecs("UTF-8");
    QApplication app(argc, argv);

    WiringForm *view = new WiringForm();
    WiringPresenter *presenter = new WiringPresenter(view);
    Q_UNUSED(presenter);
    view->show();

    return app.exec();
}

