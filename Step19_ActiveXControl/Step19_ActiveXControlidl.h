

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __Step19_ActiveXControlidl_h__
#define __Step19_ActiveXControlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef ___DStep19ActiveXControl_FWD_DEFINED__
#define ___DStep19ActiveXControl_FWD_DEFINED__
typedef interface _DStep19ActiveXControl _DStep19ActiveXControl;

#endif 	/* ___DStep19ActiveXControl_FWD_DEFINED__ */


#ifndef ___DStep19ActiveXControlEvents_FWD_DEFINED__
#define ___DStep19ActiveXControlEvents_FWD_DEFINED__
typedef interface _DStep19ActiveXControlEvents _DStep19ActiveXControlEvents;

#endif 	/* ___DStep19ActiveXControlEvents_FWD_DEFINED__ */


#ifndef __Step19ActiveXControl_FWD_DEFINED__
#define __Step19ActiveXControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class Step19ActiveXControl Step19ActiveXControl;
#else
typedef struct Step19ActiveXControl Step19ActiveXControl;
#endif /* __cplusplus */

#endif 	/* __Step19ActiveXControl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_Step19ActiveXControl_0000_0000 */
/* [local] */ 

#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(pop)
#pragma warning(pop)
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_Step19ActiveXControl_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Step19ActiveXControl_0000_0000_v0_0_s_ifspec;


#ifndef __Step19ActiveXControlLib_LIBRARY_DEFINED__
#define __Step19ActiveXControlLib_LIBRARY_DEFINED__

/* library Step19ActiveXControlLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_Step19ActiveXControlLib;

#ifndef ___DStep19ActiveXControl_DISPINTERFACE_DEFINED__
#define ___DStep19ActiveXControl_DISPINTERFACE_DEFINED__

/* dispinterface _DStep19ActiveXControl */
/* [uuid] */ 


EXTERN_C const IID DIID__DStep19ActiveXControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5a3a3dca-965a-4d7b-ab92-d49ce81dea7d")
    _DStep19ActiveXControl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DStep19ActiveXControlVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DStep19ActiveXControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DStep19ActiveXControl * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DStep19ActiveXControl * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DStep19ActiveXControl * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DStep19ActiveXControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DStep19ActiveXControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DStep19ActiveXControl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DStep19ActiveXControlVtbl;

    interface _DStep19ActiveXControl
    {
        CONST_VTBL struct _DStep19ActiveXControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DStep19ActiveXControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DStep19ActiveXControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DStep19ActiveXControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DStep19ActiveXControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DStep19ActiveXControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DStep19ActiveXControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DStep19ActiveXControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DStep19ActiveXControl_DISPINTERFACE_DEFINED__ */


#ifndef ___DStep19ActiveXControlEvents_DISPINTERFACE_DEFINED__
#define ___DStep19ActiveXControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DStep19ActiveXControlEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DStep19ActiveXControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("daf4e232-181d-4a49-b011-2e079d55cbe6")
    _DStep19ActiveXControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DStep19ActiveXControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DStep19ActiveXControlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DStep19ActiveXControlEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DStep19ActiveXControlEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DStep19ActiveXControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DStep19ActiveXControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DStep19ActiveXControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DStep19ActiveXControlEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DStep19ActiveXControlEventsVtbl;

    interface _DStep19ActiveXControlEvents
    {
        CONST_VTBL struct _DStep19ActiveXControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DStep19ActiveXControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DStep19ActiveXControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DStep19ActiveXControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DStep19ActiveXControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DStep19ActiveXControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DStep19ActiveXControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DStep19ActiveXControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DStep19ActiveXControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Step19ActiveXControl;

#ifdef __cplusplus

class DECLSPEC_UUID("ca2b8edd-562b-4e6c-b8e7-f0839397949c")
Step19ActiveXControl;
#endif
#endif /* __Step19ActiveXControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


