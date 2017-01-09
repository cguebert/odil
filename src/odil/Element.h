/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9c3d8f32_0310_4e3a_b5d2_6d69f229a2cf
#define _9c3d8f32_0310_4e3a_b5d2_6d69f229a2cf

#include <cstddef>
#include <initializer_list>

#include "odil/odil.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"

namespace odil
{

/**
 * @brief Element of a DICOM data set.
 */
class ODIL_API Element
{
public:

    /// @brief VR of the element.
    VR vr;

    /// @brief Constructor using the VR to create an according empty container.
    Element(VR const & vr);

    /// @brief Constructor.
    Element(Value const & value, VR const & vr);

    /// @brief Constructor.
    Element(Value::Integers const & value, VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(Value::Reals const & value, VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(Value::Strings const & value, VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(Value::DataSets const & value, VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(Value::Binary const & value, VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(
        std::initializer_list<int> const & value, VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(
        std::initializer_list<Value::Integer> const & value,
        VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(
        std::initializer_list<Value::Real> const & value,
        VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(
        std::initializer_list<Value::String> const & value,
        VR const & vr=VR::INVALID);

    /// @brief Constructor.
    Element(
        std::initializer_list<DataSet> const & value,
        VR const & vr=VR::INVALID);

    /// @brief Test whether the element is empty.
    bool empty() const;

    /// @brief Return the number of items in the value.
    std::size_t size() const;

    /// @brief Return the raw value.
    Value const & get_value() const;

    /// @brief Test whether the value contains integers.
    bool is_int() const;

    /**
     * @brief Return the integers contained in the element.
     *
     * If the element does not contain integers, a odil::Exception is raised.
     */
    Value::Integers const & as_int() const;

    /**
     * @brief Return the integers contained in the element.
     *
     * If the element does not contain integers, a odil::Exception is raised.
     */
    Value::Integers & as_int();

    /// @brief Test whether the value contains reals.
    bool is_real() const;

    /**
     * @brief Return the reals contained in the element.
     *
     * If the element does not contain reals, a odil::Exception is raised.
     */
    Value::Reals const & as_real() const;

    /**
     * @brief Return the reals contained in the element.
     *
     * If the element does not contain reals, a odil::Exception is raised.
     */
    Value::Reals & as_real();

    /// @brief Test whether the value contains strings.
    bool is_string() const;

    /**
     * @brief Return the strings contained in the element.
     *
     * If the element does not contain strings, a odil::Exception is raised.
     */
    Value::Strings const & as_string() const;

    /**
     * @brief Return the strings contained in the element.
     *
     * If the element does not contain strings, a odil::Exception is raised.
     */
    Value::Strings & as_string();

    /// @brief Test whether the value contains data sets.
    bool is_data_set() const;

    /**
     * @brief Return the data sets contained in the element.
     *
     * If the element does not contain data sets, a odil::Exception is raised.
     */
    Value::DataSets const & as_data_set() const;

    /**
     * @brief Return the data sets contained in the element.
     *
     * If the element does not contain data sets, a odil::Exception is raised.
     */
    Value::DataSets & as_data_set();

    /// @brief Test whether the value contains data sets.
    bool is_binary() const;

    /**
     * @brief Return the binary data contained in the element.
     *
     * If the element does not contain binary data, a odil::Exception is raised.
     */
    Value::Binary const & as_binary() const;

    /**
     * @brief Return the binary data contained in the element.
     *
     * If the element does not contain binary data, a odil::Exception is raised.
     */
    Value::Binary & as_binary();

    /// @brief Equality test
    bool operator==(Element const & other) const;

    /// @brief Difference test
    bool operator!=(Element const & other) const;
    
    /// @brief Clear the element (element.empty() will be true).
    void clear();

private:
    Value _value;
};

/**
 * @brief Visitor of elements.
 */
template<typename TVisitor>
typename TVisitor::result_type
apply_visitor(TVisitor const & visitor, Element const & element);


}

#include "odil/Element.txx"

#endif // _9c3d8f32_0310_4e3a_b5d2_6d69f229a2cf

