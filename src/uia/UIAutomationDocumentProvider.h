/* Copyright 2013 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#ifndef UIAutomationDocumentProvider_h
#define UIAutomationDocumentProvider_h

#include <UIAutomation.h>

class DisplayModel;
class SumatraUIAutomationProvider;
class SumatraUIAutomationPageProvider;
class SumatraUIAutomationTextRange;
class SumatraUIAutomationDocumentProvider : public IRawElementProviderFragment, public IRawElementProviderSimple, public ITextProvider, public IAccIdentity {
    ULONG                               refCount;
    HWND                                canvasHwnd;
    SumatraUIAutomationProvider*        root;
    bool                                released;

    SumatraUIAutomationPageProvider*    child_first;
    SumatraUIAutomationPageProvider*    child_last;

    DisplayModel*                       dm;

public:
    SumatraUIAutomationDocumentProvider(HWND canvasHwnd, SumatraUIAutomationProvider* root);
    ~SumatraUIAutomationDocumentProvider();

    /*
     * reads page count and creates a child element for each page
     */
    void LoadDocument(DisplayModel* dm);
    void FreeDocument();
    bool IsDocumentLoaded() const;

    // GetDM() must not be called if IsDocumentLoaded()==FALSE
    DisplayModel* GetDM();

    SumatraUIAutomationPageProvider* GetFirstPage();
    SumatraUIAutomationPageProvider* GetLastPage();

    //IUnknown
    HRESULT STDMETHODCALLTYPE QueryInterface(const IID &,void **);
    ULONG   STDMETHODCALLTYPE AddRef(void);
    ULONG   STDMETHODCALLTYPE Release(void);
    
    //IRawElementProviderFragment
    HRESULT STDMETHODCALLTYPE Navigate(enum NavigateDirection direction, IRawElementProviderFragment **pRetVal);
    HRESULT STDMETHODCALLTYPE GetRuntimeId(SAFEARRAY **pRetVal);
    HRESULT STDMETHODCALLTYPE GetEmbeddedFragmentRoots(SAFEARRAY **pRetVal);
    HRESULT STDMETHODCALLTYPE SetFocus(void);
    HRESULT STDMETHODCALLTYPE get_BoundingRectangle(struct UiaRect *pRetVal);
    HRESULT STDMETHODCALLTYPE get_FragmentRoot(IRawElementProviderFragmentRoot **pRetVal);

    //IRawElementProviderSimple
    HRESULT STDMETHODCALLTYPE GetPatternProvider(PATTERNID patternId,IUnknown **pRetVal);
    HRESULT STDMETHODCALLTYPE GetPropertyValue(PROPERTYID propertyId,VARIANT *pRetVal);
    HRESULT STDMETHODCALLTYPE get_HostRawElementProvider(IRawElementProviderSimple **pRetVal);
    HRESULT STDMETHODCALLTYPE get_ProviderOptions(ProviderOptions *pRetVal);
    
    //ITextProvider
    HRESULT STDMETHODCALLTYPE GetSelection(SAFEARRAY * *pRetVal);
    HRESULT STDMETHODCALLTYPE GetVisibleRanges(SAFEARRAY * *pRetVal);
    HRESULT STDMETHODCALLTYPE RangeFromChild(IRawElementProviderSimple *childElement, ITextRangeProvider **pRetVal);
    HRESULT STDMETHODCALLTYPE RangeFromPoint( struct UiaPoint point, ITextRangeProvider **pRetVal);
    HRESULT STDMETHODCALLTYPE get_DocumentRange(  ITextRangeProvider **pRetVal);
    HRESULT STDMETHODCALLTYPE get_SupportedTextSelection( enum SupportedTextSelection *pRetVal);

    //IAccIdentity
    HRESULT STDMETHODCALLTYPE GetIdentityString(DWORD dwIDChild, BYTE **ppIDString, DWORD *pdwIDStringLen);
};

#endif //UIAutomationDocumentProvider_h