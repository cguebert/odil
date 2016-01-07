/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b76e1bde_7daf_41f4_82f1_af94e1c22285
#define _b76e1bde_7daf_41f4_82f1_af94e1c22285

#include <functional>
#include <string>
#include <utility>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>

#include "dcmtkpp/AssociationParameters.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/Network.h"

namespace dcmtkpp
{

namespace dcmtk
{

/**
 * @brief Wrapper around the T_ASC_Association class.
 *
 * No member can be set while the object is associated.
 */
class Association
{
public:
    /// @brief Association result (PS 3.8, 7.1.1.7 and PS 3.8, 9.3.4).
    enum Result
    {
        //Accepted,
        RejectedPermanent=1,
        RejectedTransient=2,
    };

    /// @brief Source of association result (PS 3.8, 7.1.1.8 and PS 3.8, 9.3.4).
    enum ResultSource
    {
        ULServiceUser=1,
        ULServiceProviderACSERelatedFunction=2,
        ULServiceProvderPresentationRelatedFunction=3,
    };

    // PS 3.8, 7.1.1.9, and PS 3.8, 9.3.4, and ITU-T X.227 (UL service-user,
    // UL service-provider ACSE-related function), ITU-T X.226 (UL
    // service-provider presentation-related function)
    /// @brief Diagnostic of association result
    enum Diagnostic
    {
        // UL service-user
        NoReasonGiven=1,
        ApplicationContextNameNotSupported=2,
        CallingAETitleNotRecognized=3,
        CallingAPInvocationIdentifierNotRecognized=4,
        CallingAEQualifierNotRecognized=5,
        CallingAEInvocationIdentifierNotRecognized=6,
        CalledAETitleNotRecognized=7,
        CalledAPInvocationIdentifierNotRecognized=8,
        CalledAEQualifierNotRecognized=9,
        CalledAEInvocationIdentifierNotRecognized=10,

        // UL service-provider, ACSE-related function
        NoCommonULVersion=2,

        // UL service-provider, presentation-related function
        TemporaryCongestion=1,
        LocalLimitExceeded=2,
        CalledPresentationAddressUnknown=3,
        PresentationProtocolVersionNotSupported=4,
        NoPresentationServiceAccessPointAvailable=7,
    };

    struct PresentationContext
    {
        std::string abstract_syntax;
        std::vector<std::string> transfer_syntaxes;
        T_ASC_SC_ROLE role;

        PresentationContext():
            abstract_syntax(""), transfer_syntaxes({}), role(ASC_SC_ROLE_DEFAULT)
        {
            // Nothing else.
        }

        PresentationContext(std::string const & abstract_s,
                            std::vector<std::string> const & transfer_s,
                            T_ASC_SC_ROLE role = ASC_SC_ROLE_DEFAULT):
            abstract_syntax(abstract_s), transfer_syntaxes(transfer_s),
            role(role)
        {
            // Nothing else.
        }
    };

    typedef AssociationParameters::UserIdentity::Type UserIdentityType;

    /// @brief Progress callback, following the semantics of DCMTK.
    typedef void(*ProgressCallback)(void *, unsigned long);

    /// @brief Wrapper class for DMCTK progress callbacks.
    struct ProgressCallbackData
    {
        /// @brief Callback function.
        ProgressCallback callback;

        /// @brief Callback data.
        void * data;
    };

    /// @brief Create a default, un-associated, association.
    Association();

    /// @brief Create an un-associated association.
    Association(Association const & other);

    /// @brief Destroy the association, release it if necessary.
    ~Association();

    /// @brief Assing an un-associated association; it remains un-associated.
    Association & operator=(Association const & other);

    /// @brief Return the AE title of the caller. Defaults to "".
    std::string const & get_own_ae_title() const;
    /// @brief Set the AE title of the caller.
    void set_own_ae_title(std::string const & ae_title);

    /// @name Peer
    /// @{

    /// @brief Return the host name of the peer. Defaults to "".
    std::string const & get_peer_host_name() const;
    /// @brief Set the host name of the peer.
    void set_peer_host_name(std::string const & host_name);

    /// @brief Return the port of the peer. Defaults to 104.
    uint16_t get_peer_port() const;
    /// @brief Set the port of the peer.
    void set_peer_port(uint16_t port);

    /// @brief Return the AE title of the peer. Defaults to "".
    std::string const & get_peer_ae_title() const;
    /// @brief Set the AE title of the peer.
    void set_peer_ae_title(std::string const & ae_title);

    /// @}

    /// @name Presentation contexts
    /// @{

    void set_presentation_contexts(
            std::vector<PresentationContext> const & presentation_contexts);

    std::vector<PresentationContext> get_presentation_contexts() const;

    /// @}

    /// @name User identity
    /// @{

    /// @brief Return the user identity type. Defaults to None.
    UserIdentityType get_user_identity_type() const;
    /// @brief Set the user identity type.
    void set_user_identity_type(UserIdentityType type);

    /// @brief Return the user identity primary field. Defaults to "".
    std::string const & get_user_identity_primary_field() const;
    /// @brief Set the user identity primary field.
    void set_user_identity_primary_field(std::string const & value);

    /// @brief Return the user identity secondary field. Defaults to "".
    std::string const & get_user_identity_secondary_field() const;
    /// @brief Set the user identity secondary field.
    void set_user_identity_secondary_field(std::string const & value);

    /// @brief Do no authenticate user.
    void set_user_identity_to_none();

    /// @brief Authenticate user using only a username.
    void set_user_identity_to_username(std::string const & username);

    /// @brief Authenticate user using a username and a password.
    void set_user_identity_to_username_and_password(
        std::string const & username, std::string const & password);

    /// @brief Authenticate user using a Kerberos ticket.
    void set_user_identity_to_kerberos(std::string const & ticket);

    /// @brief Authenticate user using a SAML assertion.
    void set_user_identity_to_saml(std::string const & assertion);

    /// @}

    /// @name Network Timeout
    /// @{

    /// @brief Set the Network timeout.
    void set_network_timeout(int timeout);

    /// @brief Return associated Network timeout.
    int get_network_timeout() const;

    /// @}

    /// @name Association
    /// @{

    /// @brief Test whether the object is currently associated to its peer.
    bool is_associated() const;

    /**
     * @brief Request an association with the peer.
     * @param network network to use for the data transmission.
     *
     * Throws an exception if already associated.
     */
    void associate(Network & network);

    /**
     * @brief Receive an association for a peer.
     * @param network network to use for the data transmission.
     * @param accept_all if true, accept all presentations contexts proposed
     *  by peer.
     *
     * All AE titles are accepted as peers, and no authentication is performed.
     */
    void receive(Network & network, bool accept_all=false);

    void receive(Network & network,
                 std::function<bool(Association const&)> authenticator,
                 std::vector<std::string> const & aetitles,
                 bool accept_all=false);

    /// @brief Reject the received association request.
    void reject(Result result, ResultSource result_source, Diagnostic diagnostic);

    /// @brief Return the association object.
    T_ASC_Association * get_association();

    /// @brief Gracefully release the association. Throws an exception if not associated.
    void release();
    /// @brief Forcefully release the association. Throws an exception if not associated.
    void abort();

    /// @brief Drop an association that has been released by the peer.
    void drop();

    /// @}

    /// @brief Receive a generic DIMSE message.
    message::Message receive(
        ProgressCallback callback=NULL, void* callback_data=NULL);

    /**
     * @brief Receive a DIMSE message of specific type.
     *
     * Throw an exception if the received message is not of the requested type.
     */
    template<typename TMessage>
    TMessage receive(ProgressCallback callback=NULL, void* callback_data=NULL);

    /// @brief Send a DIMSE message.
    void send(
        message::Message const & message, std::string const & abstract_syntax,
        ProgressCallback callback=NULL, void* callback_data=NULL);

private:
    std::string _own_ae_title;

    std::string _peer_host_name;
    uint16_t _peer_port;
    std::string _peer_ae_title;

    std::vector<PresentationContext> _presentation_contexts;

    UserIdentityType _user_identity_type;
    std::string _user_identity_primary_field;
    std::string _user_identity_secondary_field;

    T_ASC_Association * _association;

    int _network_timeout;

    /// @brief Find an accepted presentation context.
    T_ASC_PresentationContextID _find_presentation_context(
        std::string const & abstract_syntax) const;

    std::pair<DataSet, DUL_DATAPDV> _receive_dataset(
        ProgressCallback callback, void *callbackContext);

    void _send(
        DataSet const & obj, T_ASC_PresentationContextID presID,
        std::string const & transfer_syntax, DUL_DATAPDV pdvType,
        ProgressCallback callback, void *callbackContext);

    DUL_PDV _read_next_pdv();

    /// @brief Wrapper from ProgressCallback to DIMSE_ProgressCallback.
    static void _progress_callback_wrapper(void * data, unsigned long bytes_count);

};

}

}

#include "DcmtkAssociation.txx"

#endif // _b76e1bde_7daf_41f4_82f1_af94e1c22285
