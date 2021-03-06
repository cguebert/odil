/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/CMoveResponse.h"

void wrap_CMoveResponse()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::message;

    class_<CMoveResponse, bases<Response>>(
            "CMoveResponse", init<Value::Integer, Value::Integer>())
        .def(init<Value::Integer, Value::Integer, DataSet const &>())
        .def(init<Message>())
        .def("has_message_id", &CMoveResponse::has_message_id)
        .def(
            "get_message_id", &CMoveResponse::get_message_id,
            return_value_policy<copy_const_reference>())
        .def("set_message_id", &CMoveResponse::set_message_id)
        .def(
            "has_affected_sop_class_uid",
            &CMoveResponse::has_affected_sop_class_uid)
        .def(
            "get_affected_sop_class_uid",
            &CMoveResponse::get_affected_sop_class_uid,
            return_value_policy<copy_const_reference>())
        .def(
            "set_affected_sop_class_uid",
            &CMoveResponse::set_affected_sop_class_uid)
        .def(
            "has_number_of_remaining_sub_operations",
            &CMoveResponse::has_number_of_remaining_sub_operations)
        .def(
            "get_number_of_remaining_sub_operations",
            &CMoveResponse::get_number_of_remaining_sub_operations,
            return_value_policy<copy_const_reference>())
        .def(
            "set_number_of_remaining_sub_operations",
            &CMoveResponse::set_number_of_remaining_sub_operations)
        .def(
            "has_number_of_completed_sub_operations",
            &CMoveResponse::has_number_of_completed_sub_operations)
        .def(
            "get_number_of_completed_sub_operations",
            &CMoveResponse::get_number_of_completed_sub_operations,
            return_value_policy<copy_const_reference>())
        .def(
            "set_number_of_completed_sub_operations",
            &CMoveResponse::set_number_of_completed_sub_operations)
        .def(
            "has_number_of_failed_sub_operations",
            &CMoveResponse::has_number_of_failed_sub_operations)
        .def(
            "get_number_of_failed_sub_operations",
            &CMoveResponse::get_number_of_failed_sub_operations,
            return_value_policy<copy_const_reference>())
        .def(
            "set_number_of_failed_sub_operations",
            &CMoveResponse::set_number_of_failed_sub_operations)
        .def(
            "has_number_of_warning_sub_operations",
            &CMoveResponse::has_number_of_warning_sub_operations)
        .def(
            "get_number_of_warning_sub_operations",
            &CMoveResponse::get_number_of_warning_sub_operations,
            return_value_policy<copy_const_reference>())
        .def(
            "set_number_of_warning_sub_operations",
            &CMoveResponse::set_number_of_warning_sub_operations)
    ;
}
