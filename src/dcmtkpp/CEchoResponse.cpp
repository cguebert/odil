/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CEchoResponse.h"

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Response.h"

namespace dcmtkpp
{

CEchoResponse
::CEchoResponse(
    Uint16 message_id_being_responded_to, Uint16 status,
    std::string const & affected_sop_class_uid)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(DIMSE_C_ECHO_RSP);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
}

CEchoResponse
::CEchoResponse(Message const & message)
: Response(message)
{
    if(message.get_command_field() != DIMSE_C_ECHO_RSP)
    {
        throw Exception("Message is not a C-ECHO-RSP");
    }
    this->set_command_field(message.get_command_field());
    
    auto command_set = const_cast<DcmDataset &>(message.get_command_set());
    OFString affected_sop_class_uid;
    
    auto const condition = command_set.findAndGetOFString(
        DCM_AffectedSOPClassUID, affected_sop_class_uid);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    this->set_affected_sop_class_uid(affected_sop_class_uid.c_str());
}

CEchoResponse
::~CEchoResponse()
{
    // Nothing to do.
}

std::string 
CEchoResponse
::get_affected_sop_class_uid() const
{
    auto command_set = const_cast<DcmDataset &>(this->_command_set);
    OFString affected_sop_class_uid;
    
    auto const condition = command_set.findAndGetOFString(
        DCM_AffectedSOPClassUID, affected_sop_class_uid);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return affected_sop_class_uid.c_str();
}

void 
CEchoResponse
::set_affected_sop_class_uid(std::string const & affected_sop_class_uid)
{
    auto const condition = this->_command_set.putAndInsertOFStringArray(
        DCM_AffectedSOPClassUID, affected_sop_class_uid.c_str());
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}