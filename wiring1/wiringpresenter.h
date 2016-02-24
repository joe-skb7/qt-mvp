#ifndef WIRINGPRESENTER_H
#define WIRINGPRESENTER_H

#include <QObject>
#include "wiringmodel.h"

class IWiringView;

class WiringPresenter : public QObject
{
    Q_OBJECT

public:
    explicit WiringPresenter(IWiringView *view, QObject *parent = 0);

private:
    void refreshView() const;

    WiringModel *m_model;
    IWiringView *m_view;

private slots:
    void processCalcAction();
};

#endif // WIRINGPRESENTER_H
