#ifndef WIRINGPRESENTER_H
#define WIRINGPRESENTER_H

#include <QObject>
#include "wiringmodel.h"

class IWiringView;
template <typename T> class QList;

class WiringPresenter : public QObject
{
    Q_OBJECT

public:
    explicit WiringPresenter(QObject *parent = 0);

    void appendView(IWiringView *view);

private:
    void refreshView() const;
    void refreshView(IWiringView *view) const;

    WiringModel *m_model;
    QList<IWiringView*> m_viewList;

private slots:
    void processCalcAction();
};

#endif // WIRINGPRESENTER_H
