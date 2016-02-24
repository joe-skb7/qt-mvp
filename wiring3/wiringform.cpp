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

void WiringForm::setCurrent(double current)
{
    bool ok;
    double myCurrent = ui->currentEdit->text().toDouble(&ok);
    if (ok && qFuzzyCompare(myCurrent, current))
        return;
    ui->currentEdit->setText(QString::number(current, 'f', 1));
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

void WiringForm::setMaterial(WiringModel::Material material)
{
    switch (material) {
    case WiringModel::Copper:
        ui->materialComboBox->setCurrentIndex(0); // медь
        break;
    case WiringModel::Aluminium:
        ui->materialComboBox->setCurrentIndex(1); // алюминий
        break;
    case WiringModel::UndefinedMaterial:
        // Переход на следующую секцию
    default:
        qWarning() << "Unknown material in WiringForm::setMaterial()";
        return;
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

void WiringForm::on_currentEdit_textChanged(const QString &text)
{
    bool ok;
    double current = text.toDouble(&ok);
    if (ok)
        emit currentChanged(current);
}

void WiringForm::on_materialComboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0: // медь
        emit materialChanged(WiringModel::Copper);
        break;
    case 1: // алюминий
        emit materialChanged(WiringModel::Aluminium);
        break;
    default:
        qWarning() << "Unknown material in materialComboBox";
        return;
    }
}
