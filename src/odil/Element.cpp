/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Element.h"

#include "odil/Exception.h"
#include "odil/Value.h"
#include "odil/DataSet.h"

namespace odil
{

Element
::Element(VR const & vr)
: _value(Value::Integers()), vr(vr)
{
    if(odil::is_int(vr))
    {
        this->_value = Value::Integers();
    }
    else if(odil::is_real(vr))
    {
        this->_value = Value::Reals();
    }
    else if(odil::is_string(vr))
    {
        this->_value = Value::Strings();
    }
    else if(vr == VR::SQ)
    {
        this->_value = Value::DataSets();
    }
    else if(odil::is_binary(vr))
    {
        this->_value = Value::Binary();
    }
    else
    {
        throw Exception("Unknown VR type");
    }
}

Element
::Element(Value const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(Value::Integers const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(Value::Reals const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(Value::Strings const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(Value::DataSets const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(Value::Binary const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(std::initializer_list<int> const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(std::initializer_list<Value::Integer> const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(std::initializer_list<Value::Real> const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(std::initializer_list<Value::String> const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

Element
::Element(std::initializer_list<DataSet> const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

bool
Element
::empty() const
{
    return this->_value.empty();
}

std::size_t
Element
::size() const
{
    return this->_value.size();
}

Value const &
Element
::get_value() const
{
    return this->_value;
}

bool
Element
::is_int() const
{
    return (this->_value.get_type() == Value::Type::Integers);
}

Value::Integers const &
Element
::as_int() const
{
    return this->_value.as_integers();
}

Value::Integers &
Element
::as_int()
{
    return this->_value.as_integers();
}

bool
Element
::is_real() const
{
    return (this->_value.get_type() == Value::Type::Reals);
}

Value::Reals const &
Element
::as_real() const
{
    return this->_value.as_reals();
}

Value::Reals &
Element
::as_real()
{
    return this->_value.as_reals();
}

bool
Element
::is_string() const
{
    return (this->_value.get_type() == Value::Type::Strings);
}

Value::Strings const &
Element
::as_string() const
{
    return this->_value.as_strings();
}

Value::Strings &
Element
::as_string()
{
    return this->_value.as_strings();
}

bool
Element
::is_data_set() const
{
    return (this->_value.get_type() == Value::Type::DataSets);
}

Value::DataSets const &
Element
::as_data_set() const
{
    return this->_value.as_data_sets();
}

Value::DataSets &
Element::as_data_set()
{
    return this->_value.as_data_sets();
}

bool
Element
::is_binary() const
{
    return (this->_value.get_type() == Value::Type::Binary);
}

Value::Binary const &
Element
::as_binary() const
{
    return this->_value.as_binary();
}

Value::Binary &
Element::as_binary()
{
    return this->_value.as_binary();
}

bool
Element
::operator==(Element const & other) const
{
    return (this->vr == other.vr) && (this->_value == other._value);
}

bool
Element
::operator!=(Element const & other) const
{
    return !(*this == other);
}

void
Element
::clear()
{
    this->_value.clear();
}

}

