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
    void setCurrent(double current);
    WiringModel::Material material() const;
    void setMaterial(WiringModel::Material material);
    void setSection(double section);
    void setCalcResult(WiringModel::CalcResult result);

signals:
    void calcActionTriggered();
    void materialChanged(WiringModel::Material material);
    void currentChanged(double current);

private:
    Ui::WiringForm *ui;

private slots:
    void on_materialComboBox_currentIndexChanged(int index);
    void on_currentEdit_textChanged(const QString &text);
    void on_calcButton_clicked();
};

#endif // WIRINGFORM_H
