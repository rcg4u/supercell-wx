#pragma once

#include <memory>
#include <string>

#include <scwx/qt/types/font_types.hpp>

struct ImFont;

namespace scwx
{
namespace qt
{
namespace types
{

class ImGuiFont
{
public:
   explicit ImGuiFont(const std::string&    fontName,
                      const std::string&    fontData,
                      units::pixels<double> size);
   ~ImGuiFont();

   ImGuiFont(const ImGuiFont&)            = delete;
   ImGuiFont& operator=(const ImGuiFont&) = delete;

   ImGuiFont(ImGuiFont&&)            = delete;
   ImGuiFont& operator=(ImGuiFont&&) = delete;

   ImFont* font();

private:
   class Impl;
   std::unique_ptr<Impl> p;
};

} // namespace types
} // namespace qt
} // namespace scwx
