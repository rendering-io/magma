#include "internal.h"
#include <dlfcn.h>

namespace {
using void_fn = void (*)();

class loader {
public:
  loader();
  ~loader();

  template <typename F>
  auto get_instance_fn(VkInstance instance, const char *name, F &f) -> void;

private:
  void *_module;
  PFN_vkGetInstanceProcAddr _get_instance_proc_addr;
};

auto get_loader() -> loader & {
  static loader l;
  return l;
}

loader::loader() : _module{dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL)} {
  _get_instance_proc_addr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
      dlsym(_module, "vkGetInstanceProcAddr"));
}

loader::~loader() { dlclose(_module); }

template <typename F>
auto loader::get_instance_fn(VkInstance instance, const char *name, F &f)
    -> void {
  f = reinterpret_cast<F>(_get_instance_proc_addr(instance, name));
}

} // namespace

namespace magma {
namespace vk {
namespace internal {

auto get_global_fn(global_fn_table &t) -> void {
  auto &l = get_loader();
  l.get_instance_fn(VK_NULL_HANDLE, "vkCreateInstance", t.create_instance);
}

auto get_instance_fn(VkInstance instance, instance_fn_table &t) -> void {
  auto &l = get_loader();
  l.get_instance_fn(instance, "vkDestroyInstance", t.destroy_instance);
  l.get_instance_fn(instance, "vkEnumeratePhysicalDevices",
                    t.enumerate_physical_devices);
}

} // namespace internal
} // namespace vk
} // namespace magma
