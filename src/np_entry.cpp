#include <npfunctions.h>

NPNetscapeFuncs* g_npnfuncs = NULL;

NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* nppfuncs) {
  if (nppfuncs == nullptr) return NPERR_INVALID_FUNCTABLE_ERROR;
  nppfuncs->version = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
  nppfuncs->newp = NPP_New;
  nppfuncs->destroy = NPP_Destroy;
  nppfuncs->getvalue = NPP_GetValue;
  return NPERR_NO_ERROR;
}

NPError OSCALL NP_Initialize(NPNetscapeFuncs* npnf) {
  if (npnf == nullptr) return NPERR_INVALID_FUNCTABLE_ERROR;
  if (HIBYTE(npnf->version) > NP_VERSION_MAJOR)
    return NPERR_INCOMPATIBLE_VERSION_ERROR;
  g_npnfuncs = npnf;
  return NPERR_NO_ERROR;
}

NPError OSCALL NP_Shutdown() { return NPERR_NO_ERROR; }

// Needs to be present for WebKit based browsers.
NPError OSCALL NP_GetValue(void* npp, NPPVariable variable, void* value) {
  return NPP_GetValue((NPP)npp, variable, value);
}
