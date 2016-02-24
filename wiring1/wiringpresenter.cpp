#include "wiringpresenter.h"
#include "iwiringview.h"

/*!
    \class WiringPresenter

    "Представитель" в триаде MVP расчета электропроводки.
*/

WiringPresenter::WiringPresenter(IWiringView *view, QObject *parent)
    : QObject(parent), m_model(new WiringModel), m_view(view)
{
    QObject *view_obj = dynamic_cast<QObject*>(m_view);
    QObject::connect(view_obj, SIGNAL(calcActionTriggered()),
                     this, SLOT(processCalcAction()));
    refreshView();
}

/*!
    Обновить представление.
*/
void WiringPresenter::refreshView() const
{
    m_view->setCalcResult(m_model->result());
    if (m_model->result() == WiringModel::Ok)
        m_view->setSection(m_model->section());
}

/*!
    Расчет сечения проводника (обработчик действия пользователя "Расчет").
*/
void WiringPresenter::processCalcAction()
{
    m_model->setCurrent(m_view->current());
    m_model->setMaterial(m_view->material());
    m_model->calc();
    refreshView();
}
