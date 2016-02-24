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

    WiringForm *view1 = new WiringForm();
    WiringForm *view2 = new WiringForm();
    WiringForm *view3 = new WiringForm();

    WiringPresenter *presenter = new WiringPresenter();
    presenter->appendView(view1);
    presenter->appendView(view2);
    presenter->appendView(view3);

    view1->show();
    view2->show();
    view3->show();

    return app.exec();
}

