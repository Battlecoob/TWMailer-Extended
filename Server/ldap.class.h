#include <ldap.h>
#include <iostream>

#include "../Other/functions.h"

#define FH_LDAP_SEARCHBASE "dc=technikum-wien,dc=at"
#define FH_LDAP_URI "ldap://ldap.technikum-wien.at:389"

class LDAPClass
{
private:

    int _version;
    bool _connected;  
    LDAP* _ldapHandle;

public:
    LDAPClass();
    ~LDAPClass();

    void LDAPConnect();
    bool LDAPLogin(const std::string&, const std::string&);
    const bool IsConnected() { return _connected; }
};