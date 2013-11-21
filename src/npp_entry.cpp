#include "plugin.h"

static NPClass kNpClass = {
    NP_CLASS_STRUCT_VERSION, Plugin::Allocate,    Plugin::Deallocate,
    NULL,                    Plugin::HasMethod,   Plugin::Invoke,
    Plugin::InvokeDefault,   Plugin::HasProperty, Plugin::GetProperty,
    NULL,                    NULL, };

NPError NPP_GetValue(NPP instance, NPPVariable variable, void* value) {
  switch (variable) {
    case NPPVpluginScriptableNPObject: {
      if (instance == nullptr) return NPERR_INVALID_INSTANCE_ERROR;
      if (instance->pdata == nullptr) return NPERR_GENERIC_ERROR;
      *(NPObject**)value = (NPObject*)instance->pdata;
      break;
    }
    default:
      return NPERR_GENERIC_ERROR;
  }
  return NPERR_NO_ERROR;
}

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode,
                int16_t argc, char* argn[], char* argv[], NPSavedData* saved) {
  if (instance == nullptr) return NPERR_INVALID_INSTANCE_ERROR;

  // NPPVpluginWindowBool: Sets windowed/windowless mode for plugin display;
  // true=windowed, false=windowless
  bool windowed = false;
  g_npnfuncs->setvalue(instance, NPPVpluginWindowBool, (void*)windowed);

  instance->pdata = g_npnfuncs->createobject(instance, &kNpClass);
  // Retain the object since we keep it in plugin code
  // so that it won't be freed by browser.
  g_npnfuncs->retainobject((NPObject*)instance->pdata);

  return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save) {
  if (instance == nullptr) return NPERR_INVALID_INSTANCE_ERROR;

  if (instance->pdata != nullptr) {
    g_npnfuncs->releaseobject((NPObject*)instance->pdata);
    instance->pdata = nullptr;
  }
  return NPERR_NO_ERROR;
}
