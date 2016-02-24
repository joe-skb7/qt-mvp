#ifndef IWIRINGVIEW_H
#define IWIRINGVIEW_H

#include "wiringmodel.h"

/*!
    \interface IWiringView

    Интерфейс представления в триаде MVP расчета электропроводки.
*/

class IWiringView
{
public:
    virtual double current() const = 0;
    virtual WiringModel::Material material() const = 0;
    virtual void setSection(double section) = 0;
    virtual void setCalcResult(WiringModel::CalcResult result) = 0;

public: // signals
    virtual void calcActionTriggered() = 0;
};

#endif // IWIRINGVIEW_H
