#ifndef WIRINGFORM_H
#define WIRINGFORM_H

#include <QWidget>
#include "iwiringview.h"

namespace Ui {
    class WiringForm;
}

class WiringForm : public QWidget, public IWiringView
{
    Q_OBJECT

public:
    explicit WiringForm(QWidget *parent = 0);
    ~WiringForm();

    double current() const;
    WiringModel::Material material() const;
    void setSection(double section);
    void setCalcResult(WiringModel::CalcResult result);

signals:
    void calcActionTriggered();

private:
    Ui::WiringForm *ui;

private slots:
    void on_calcButton_clicked();
};

#endif // WIRINGFORM_H
