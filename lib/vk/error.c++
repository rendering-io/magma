#include <system_error>

namespace magma {
namespace vk {
namespace internal {

struct error_category : std::error_category {
public:
  auto name() const noexcept -> const char * override;
  auto message(int ev) const -> std::string override;
};

auto error_category::name() const noexcept -> const char * { return "Vulkan"; }

auto error_category::message(int e) const -> std::string {
  switch (e) {
  default:
    return "Unrecognized error.";
  }
}

auto get_error_category() -> const std::error_category & {
  static error_category category;
  return category;
}

} // namespace internal
} // namespace vk
} // namespace magma

