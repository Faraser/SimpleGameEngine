#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <string>
#include <glm/glm.hpp>

namespace Engine {
class GUI {
public:
    void init(const std::string& resourceDirectory);

    void destroy();

    void draw();

    void loadScheme(const std::string& schemeFile);

    void setFont(const std::string& fontFile);

    static void setWidgetDestRect(CEGUI::Window * widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

    static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }

    const CEGUI::GUIContext* getContext() const { return m_context; }

    CEGUI::Window* createWidget(const std::string type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix,
                                const std::string name = "");

private:
    static CEGUI::OpenGL3Renderer* m_renderer;
    CEGUI::GUIContext* m_context = nullptr;
    CEGUI::Window* m_root = nullptr;
};
}


