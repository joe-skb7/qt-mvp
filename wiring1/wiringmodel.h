#ifndef WIRINGMODEL_H
#define WIRINGMODEL_H

class WiringModel
{
public:
    enum Material {
        UndefinedMaterial = 0, /*!< Материал не определен */
        Copper,                /*!< Медь */
        Aluminium              /*!< Алюминий */
    };
    enum CalcResult {
        UndefinedResult = 0, /*!< Результат не определен */
        Ok,                  /*!< Расчет проведен успешно */
        WireNotFound,        /*!< Подходящее сечение не найдено */
        Error                /*!< Ошибка при расчете */
    };

public:
    WiringModel();

    Material material() const;
    void setMaterial(Material material);
    double current() const;
    void setCurrent(double current);
    void calc();
    CalcResult result() const;
    double section() const;

private:
    struct DataField {
        double section; // сечение, мм^2
        double current; // ток, А
    };
    static const DataField CopperData[];
    static const DataField AluminiumData[];

private:
    CalcResult lookupSection(const DataField *data, int size);

    Material m_material;
    double m_current;
    CalcResult m_result;
    double m_section;
};

#endif // WIRINGMODEL_H
