#include "plugin.h"

Plugin::Plugin(NPP instance) : instance_(instance) {}

NPObject* Plugin::Allocate(NPP instance, NPClass* npclass) {
  return (NPObject*)(new Plugin(instance));
}

void Plugin::Deallocate(NPObject* obj) { delete (Plugin*)obj; }

bool Plugin::HasMethod(NPObject* obj, NPIdentifier method_name) { return true; }

bool Plugin::InvokeDefault(NPObject* obj, const NPVariant* args,
                           uint32_t arg_count, NPVariant* result) {
  return true;
}

bool Plugin::Invoke(NPObject* obj, NPIdentifier method_name,
                    const NPVariant* args, uint32_t args_count,
                    NPVariant* result) {
  g_npnfuncs->setexception(obj, "Unknown method passed to npadblock");
  return false;
}

bool Plugin::HasProperty(NPObject* obj, NPIdentifier property_name) {
  return false;
}

bool Plugin::GetProperty(NPObject* obj, NPIdentifier property_name,
                         NPVariant* result) {
  return false;
}
