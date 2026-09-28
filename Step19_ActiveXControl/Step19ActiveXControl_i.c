

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Step19ActiveXControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_Step19ActiveXControlLib,0x05e6855b,0xe638,0x45d5,0xb7,0x98,0x8a,0x7c,0x6f,0x17,0xf1,0x83);


MIDL_DEFINE_GUID(IID, DIID__DStep19ActiveXControl,0x5a3a3dca,0x965a,0x4d7b,0xab,0x92,0xd4,0x9c,0xe8,0x1d,0xea,0x7d);


MIDL_DEFINE_GUID(IID, DIID__DStep19ActiveXControlEvents,0xdaf4e232,0x181d,0x4a49,0xb0,0x11,0x2e,0x07,0x9d,0x55,0xcb,0xe6);


MIDL_DEFINE_GUID(CLSID, CLSID_Step19ActiveXControl,0xca2b8edd,0x562b,0x4e6c,0xb8,0xe7,0xf0,0x83,0x93,0x97,0x94,0x9c);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



