#include "wiringmodel.h"

// Количество элементов в массиве
#define NELEMS(array) (sizeof(array) / sizeof(array[0]))

// Данные взяты с http://www.elecab.ru/prov18.shtml

// Сечение медных проводов для тока
const WiringModel::DataField WiringModel::CopperData[] = {
    { 1,   16  },
    { 1.5, 19  },
    { 2.5, 27  },
    { 4,   38  },
    { 6,   46  },
    { 10,  70  },
    { 16,  85  },
    { 25,  115 },
    { 35,  135 },
    { 50,  185 },
    { 70,  225 },
    { 95,  275 },
    { 120, 315 }
};

// Сечение алюминиевых проводов для тока
const WiringModel::DataField WiringModel::AluminiumData[] = {
    { 2.5, 20  },
    { 4,   28  },
    { 10,  50  },
    { 16,  60  },
    { 25,  85  },
    { 35,  100 },
    { 50,  140 },
    { 70,  175 },
    { 95,  215 },
    { 120, 245 }
};

/*!
    \class WiringModel

    \brief Модель расчета электропроводки.
*/

WiringModel::WiringModel()
    : m_material(Copper), m_current(0), m_result(UndefinedResult), m_section(0)
{
}

/*!
    Возвращает установленный материал проводника.

    \sa setMaterial()
*/
WiringModel::Material WiringModel::material() const
{
    return m_material;
}

/*!
    Устанавливает материал проводника.

    \sa material()
*/
void WiringModel::setMaterial(Material material)
{
    m_material = material;
}

/*!
    Возвращает установленный продолжительный ток, А.

    \sa setCurrent()
*/
double WiringModel::current() const
{
    return m_current;
}

/*!
    Устанавливает продолжительный ток, А.

    \sa current()
*/
void WiringModel::setCurrent(double current)
{
    m_current = current;
}

/*!
    Расчитывает поперечное сечение по заданному току и материалу.

    \sa result(), section()
*/
void WiringModel::calc()
{
    // Валидация входных данных
    if (m_current <= 0.001 || m_material == UndefinedMaterial) {
        m_result = Error;
        return;
    }

    // Определение таблицы данных
    switch (m_material) {
    case Copper:
        m_result = lookupSection(CopperData, NELEMS(CopperData));
        break;
    case Aluminium:
        m_result = lookupSection(AluminiumData, NELEMS(AluminiumData));
        break;
    default:
        m_result = UndefinedResult;
        return;
    }
}

/*!
    Возвращает результат последнего расчета.

    \sa section(), calc()
*/
WiringModel::CalcResult WiringModel::result() const
{
    return m_result;
}

/*!
    Возвращает последнее расчитанное попреречное сечение проводника.

    \sa result(), calc()
*/
double WiringModel::section() const
{
    return m_section;
}

/*!
    Поиск подходящего сечения для заданных в модель материала и тока.
*/
WiringModel::CalcResult WiringModel::lookupSection(const DataField *data, int size)
{
    for (int i = 0; i < size; ++i) {
        if (data[i].current >= m_current) {
            m_section = data[i].section;
            return Ok;
        }
    }
    return WireNotFound;
}
