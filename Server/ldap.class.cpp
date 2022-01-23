#include "ldap.class.h"

using std::string;

LDAPClass::LDAPClass()
{
    _ldapHandle = nullptr;
    _connected = false;
    _version = LDAP_VERSION3;
}

LDAPClass::~LDAPClass()
{
    ldap_unbind_ext_s(_ldapHandle, nullptr, nullptr);
}

void LDAPClass::LDAPConnect()
{
    // std::cout << "ldap connecting..." << std::endl;

    // int rc = ldap_initialize(&_ldapHandle, FH_LDAP_URI);
    // if(rc != LDAP_SUCCESS)
    //     PrintErrorAndExitFail("Error while initializing Ldap client.");

    // std::cout << "ldap_initialize..." << std::endl;
    
    // rc = ldap_set_option(_ldapHandle, LDAP_OPT_PROTOCOL_VERSION, &_version);
    // if(rc != LDAP_SUCCESS)
    //     PrintErrorAndExitFail("Error while setting Ldap client version.");

    // std::cout << "ldap_set_option..." << std::endl;

    // rc = ldap_start_tls_s(_ldapHandle, nullptr, nullptr);
    // if (rc != LDAP_SUCCESS)
    //     PrintErrorAndExitFail("Error in ldap_start_tls_s().");

    // std::cout << "ldap_start_tls_s..." << std::endl;

    // std::cout << "ldap connected." << std::endl;
    // _connected = true;
    int rc = ldap_initialize(&_ldapHandle, FH_LDAP_URI);

    if(rc != LDAP_SUCCESS)
    {
        std::cout << "ldap_init failed" << std::endl;
    }
    
    rc = ldap_set_option(
        _ldapHandle,
        LDAP_OPT_PROTOCOL_VERSION,
        &_version
    );
    
    if(rc != LDAP_OPT_SUCCESS)
    {
        std::cout << "ldap_set_option(PROTOCOL_VERSION): " << ldap_err2string(rc) << std::endl;
        ldap_unbind_ext_s(_ldapHandle, NULL, NULL);
    }

    rc = ldap_start_tls_s(
        _ldapHandle,
        NULL,
        NULL
    );

    if(rc != LDAP_SUCCESS)
    {
        std::cout << "ldap_start_tls_s(): " << ldap_err2string(rc) << std::endl;
        ldap_unbind_ext_s(_ldapHandle, NULL, NULL);
    }
}

bool LDAPClass::LDAPLogin(const string& username, const string& password)
{
    BerValue bindCredentials;
    bindCredentials.bv_val = (char*) password.data();
    bindCredentials.bv_len = password.length();

    string ldapBindUser = "uid=" + username + ",ou=people,dc=technikum-wien,dc=at";

    int rc = ldap_sasl_bind_s(_ldapHandle, ldapBindUser.data(), LDAP_SASL_SIMPLE, &bindCredentials, nullptr, nullptr, nullptr);
    if(rc != LDAP_SUCCESS)
        PrintErrorAndExitFail("Error while authenticating user.");

    if(rc != LDAP_INVALID_CREDENTIALS)
        return true;
    
    return false;
}