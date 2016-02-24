#include <QDebug>
#include "wiringform.h"
#include "ui_wiringform.h"

/*!
    \class WiringForm

    Представление (View) в триаде MVP расчета электропроводки.
*/

WiringForm::WiringForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::WiringForm)
{
    ui->setupUi(this);
    setFixedSize(size());
}

WiringForm::~WiringForm()
{
    delete ui;
}

/* Реализация интерфейса */

double WiringForm::current() const
{
    return ui->currentEdit->text().toDouble();
}

WiringModel::Material WiringForm::material() const
{
    switch (ui->materialComboBox->currentIndex()) {
    case 0: // медь
        return WiringModel::Copper;
    case 1: // алюминий
        return WiringModel::Aluminium;
    default:
        qWarning() << "Unknown material in materialComboBox";
        return WiringModel::UndefinedMaterial;
    }
}

void WiringForm::setSection(double section)
{
    ui->wireSectionLabel->setText(QString::number(section, 'f', 1));
}

void WiringForm::setCalcResult(WiringModel::CalcResult result)
{
    switch (result) {
    case WiringModel::Ok:
        break;
    case WiringModel::UndefinedResult:
        ui->wireSectionLabel->clear();
        break;
    case WiringModel::WireNotFound:
        ui->wireSectionLabel->setText(tr("<font color=\"red\">Сечение не найдено</font>"));
        break;
    case WiringModel::Error:
        // Переход на следующую секцию
    default:
        ui->wireSectionLabel->setText(tr("<font color=\"red\">Ошибка при расчете!</font>"));
        break;
    }
}

void WiringForm::on_calcButton_clicked()
{
    emit calcActionTriggered();
}
