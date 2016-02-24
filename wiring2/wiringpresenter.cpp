#include <QList>
#include "wiringpresenter.h"
#include "iwiringview.h"

/*!
    \class WiringPresenter

    "Представитель" в триаде MVP расчета электропроводки.
*/

WiringPresenter::WiringPresenter(QObject *parent)
    : QObject(parent), m_model(new WiringModel)
{
}

/*!
    Добавить представление \a view.
*/
void WiringPresenter::appendView(IWiringView *view)
{
    if (m_viewList.contains(view))
        return;
    m_viewList.append(view);
    QObject *view_obj = dynamic_cast<QObject*>(view);
    QObject::connect(view_obj, SIGNAL(calcActionTriggered()),
                     this, SLOT(processCalcAction()));
    refreshView(view);
}

/*!
    Обновить представление \a view.
*/
void WiringPresenter::refreshView(IWiringView *view) const
{
    view->setCalcResult(m_model->result());
    if (m_model->result() == WiringModel::Ok)
        view->setSection(m_model->section());
}

/*!
    Обновить все представления в списке презентера.
*/
void WiringPresenter::refreshView() const
{
    for (QList<IWiringView*>::const_iterator it = m_viewList.constBegin();
    it != m_viewList.constEnd(); ++it) {
        refreshView(*it);
    }
}

/*!
    Расчет сечения проводника (обработчик действия пользователя "Расчет").
*/
void WiringPresenter::processCalcAction()
{
    IWiringView *view = dynamic_cast<IWiringView*>(sender());
    m_model->setCurrent(view->current());
    m_model->setMaterial(view->material());
    m_model->calc();
    refreshView();
}
