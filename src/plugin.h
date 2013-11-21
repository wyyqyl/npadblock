#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include <npfunctions.h>

extern NPNetscapeFuncs* g_npnfuncs;

class Plugin {
 public:
  Plugin(NPP instance);
  static NPObject* Allocate(NPP instance, NPClass* npclass);
  static void Deallocate(NPObject* obj);
  static bool HasMethod(NPObject* obj, NPIdentifier methodName);
  static bool InvokeDefault(NPObject* obj, const NPVariant* args,
                            uint32_t argCount, NPVariant* result);
  static bool Invoke(NPObject* obj, NPIdentifier methodName,
                     const NPVariant* args, uint32_t argCount,
                     NPVariant* result);
  static bool HasProperty(NPObject* obj, NPIdentifier propertyName);
  static bool GetProperty(NPObject* obj, NPIdentifier propertyName,
                          NPVariant* result);

 private:
  NPP instance_;
};

#endif  // __PLUGIN_H__
