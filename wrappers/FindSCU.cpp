/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/FindSCU.h"

namespace
{

void 
find_with_python_callback(
    odil::FindSCU const & scu, 
    odil::DataSet const & query, boost::python::object const & f)
{
    scu.find(
        query, 
        [f](odil::DataSet const & data_set) 
        { 
            boost::python::call<void>(f.ptr(), data_set); 
        }
    );
}

}

void wrap_FindSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<FindSCU>("FindSCU", init<Association &>())
        .def(
            "find",
            &find_with_python_callback
        )
        .def(
            "find", 
            static_cast<
                std::vector<DataSet> (FindSCU::*)(DataSet const &) const
            >(&FindSCU::find)
        )
        .def("set_affected_sop_class", &FindSCU::set_affected_sop_class)
    ;
}
