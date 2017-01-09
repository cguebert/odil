/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7e193624_081c_47dd_a011_986e96916ea9
#define _7e193624_081c_47dd_a011_986e96916ea9

#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-STORE-RSP message.
class ODIL_API CStoreResponse: public Response
{
public:
    /// @brief C-STORE status codes, PS 3.4, B.2.3
    enum Status
    {
        // Failure
        RefusedOutOfResources=0xA700,
        ErrorDataSetDoesNotMatchSOPClass=0xA900,
        ErrorCannotUnderstand=0xC000,
        // Warning
        CoercionOfDataElements=0xB000,
        DataSetDoesNotMatchSOPClass=0xB007,
        ElementsDiscarded=0xB006,
    };

    /**
     * @brief Create an store response with given Message ID, and status.
     */
    CStoreResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status);

    /**
     * @brief Create a C-STORE-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-STORE-RSP.
     */
    CStoreResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CStoreResponse();

    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(message_id, registry::MessageID)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_instance_uid, registry::AffectedSOPInstanceUID)
};

}

}

#endif // _7e193624_081c_47dd_a011_986e96916ea9
