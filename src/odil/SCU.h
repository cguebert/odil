/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ba1518e7_8123_46c9_81c0_65439717e40e
#define _ba1518e7_8123_46c9_81c0_65439717e40e

#include <string>

#include "odil/Association.h"
#include "odil/odil.h"

namespace odil
{

/// @brief Base class for all Service Class Users.
class ODIL_API SCU
{
public:
    /// @brief Create a default Service Class User.
    SCU(Association & association);

    /// @brief Destructor.
    virtual ~SCU();
    
    /// @brief Return the affected SOP class. Defaults to "".
    std::string const & get_affected_sop_class() const;
    /// @brief Set the affected SOP class
    void set_affected_sop_class(std::string const & sop_class);
    
protected:
    /// @brief Association with peer.
    Association & _association;
    
    /// @brief Affected SOP class.
    std::string _affected_sop_class;
};

}

#endif // _ba1518e7_8123_46c9_81c0_65439717e40e
