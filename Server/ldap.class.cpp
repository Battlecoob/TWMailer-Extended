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
    int rc = ldap_initialize(&_ldapHandle, FH_LDAP_URI);
    if(rc != LDAP_SUCCESS)
        PrintErrorAndExitFail("Error while initializing Ldap client.");
    
    rc = ldap_set_option(_ldapHandle, LDAP_OPT_PROTOCOL_VERSION, &_version);
    if(rc != LDAP_SUCCESS)
        PrintErrorAndExitFail("Error while setting Ldap client version.");

    rc = ldap_start_tls_s(_ldapHandle, nullptr, nullptr);
    if (rc != LDAP_SUCCESS)
        PrintErrorAndExitFail("Error in ldap_start_tls_s().");

    _connected = true;
}

bool LDAPClass::LDAPLogin(const string& username, const string& password)
{
    BerValue bindCredentials;
    bindCredentials.bv_val = (char*) password.data();
    bindCredentials.bv_len = password.length();

    string ldapBindUser = "uid=" + username + ",ou=people,dc=technikum-wien,dc=at";

    int rc = ldap_sasl_bind_s(_ldapHandle, ldapBindUser.data(), LDAP_SASL_SIMPLE, &bindCredentials, nullptr, nullptr, nullptr);
    if(rc != LDAP_SUCCESS && rc != LDAP_INVALID_CREDENTIALS)
        PrintErrorAndExitFail("Error while authenticating user.");

    if(rc != LDAP_INVALID_CREDENTIALS)
        return true;
    
    return false;
}