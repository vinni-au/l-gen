/* Begin of file: mcr.cpp */

#include "mcr.hpp"
#undef UNICODE
#include <assert.h>
#include <QDebug>

MCR::MCR()
{
    assert(LoadMCRDLL() == true);
    (*pInit)();
}

MCR::~MCR()
{
    ReleaseMCRDLL();
}

bool MCR::LoadMCRDLL()
{
    HINSTANCE hDll = LoadLibrary("./data/mcr.dll");
    if (hDll == NULL)
        return false;

    pInit    =  (p1Func)GetProcAddress(hDll,"InitMcr");
    pLoad    =  (p2Func)GetProcAddress(hDll,"LoadMcr");
    pSave    =  (p3Func)GetProcAddress(hDll,"SaveMcr");
    pFind    =  (p4Func)GetProcAddress(hDll,"FindWID");
    pGetById =  (p5Func)GetProcAddress(hDll,"GetWordById");
    pROnly   =  (p6Func)GetProcAddress(hDll,"ReadOnlyDict");
    pAdd     =  (p7Func)GetProcAddress(hDll,"AddParadigma");
    pSpace   =  (p8Func)GetProcAddress(hDll,"FreeSpace");
    pVer     =  (p9Func)GetProcAddress(hDll,"Ver");
    pCGD     = (p10Func)GetProcAddress(hDll,"ConstIdToStr");
    pVGD     = (p11Func)GetProcAddress(hDll,"VarIdToStr");
    pFGD     = (p12Func)GetProcAddress(hDll,"GetBGH");

    if (pInit && pLoad && pSave && pGetById && pROnly && pAdd && pSpace &&
        pVer  && pCGD  && pVGD  && pFGD)
        return true;
    else {
        FreeLibrary(hDll);
        return false;
    }
}

void MCR::ReleaseMCRDLL()
{
    FreeLibrary(hDll);
}

bool MCR::LoadVocabulary(const char *filename)
{
    int res = (*pLoad)(filename);
    if (res <= 0)
        return false;
    readOnly = (*pROnly)();
    return true;
}

bool MCR::SaveVocabulary(const char *filename)
{
    int res = (*pSave)(filename);
    if (res <= 0)
        return false;
    else return true;
}

WordForms* MCR::FindWordForms(const char *word)
{
    WordForms *result = new WordForms;

    (*pFind)(word, result);

    return result;
}

Words* MCR::GetLexemByID(const WordForm id, const bool grCharOnly, const bool all)
{
    Words *result = new Words;

    (*pGetById)(id, grCharOnly, all, result);

    return result;
}

bool MCR::AddParadigm(Words *lexData)
{
    if ((*pAdd)(lexData))
        return true;
    else return false;
}

char* MCR::ConstGrammarChar(const unsigned char cid)
{
    return (*pCGD)(cid);
}

char* MCR::VarGrammarChar(const unsigned char cid, const unsigned char vid)
{
    return (*pVGD)(cid, vid);
}

Words* MCR::FindLexems(const int pn, const unsigned char cid,
                           const unsigned char vid, const bool all)
{
    Words* result = new Words;

    (*pFGD)(pn, cid, vid, all, result);

    return result;
}

Word* MCR::FindLemma(const char *word)
{
    MCR mcr;
    mcr.LoadVocabulary("./data/zal.mcr");
    WordForms* wfs = mcr.FindWordForms(word);
    if (wfs->count == 0)
        return 0;
    else return &(mcr.GetLexemByID(wfs->ids[0], false, true)->inlex[0]);
}

/* End of file: mcr.cpp */
