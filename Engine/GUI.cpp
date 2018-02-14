#include "GUI.h"

namespace Engine {

CEGUI::OpenGL3Renderer* GUI::m_renderer = nullptr;

void GUI::init(const std::string& resourceDirectory) {
    // Check if the render and systems were already initialized
    if (m_renderer == nullptr) {
        m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

        auto rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
        rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
        rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
        rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
        rp->setResourceGroupDirectory("looknfeel", resourceDirectory + "/looknfeel/");
        rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");

        CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
        CEGUI::Scheme::setDefaultResourceGroup("schemes");
        CEGUI::Font::setDefaultResourceGroup("fonts");
        CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
        CEGUI::WindowManager::setDefaultResourceGroup("layouts");
        CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    }

    m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
    m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
    m_context->setRootWindow(m_root);
}

void GUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void GUI::draw() {
    m_renderer->beginRendering();
    m_context->draw();
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}

void GUI::loadScheme(const std::string& schemeFile) {
    CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void GUI::setFont(const std::string& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context->setDefaultFont(fontFile);
}

CEGUI::Window* GUI::createWidget(const std::string type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix,
                                 const std::string name) {
    CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
//    newWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
//    newWindow->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
    setWidgetDestRect(newWindow, destRectPerc, destRectPix);
    m_root->addChild(newWindow);
    return newWindow;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix) {
    widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
    widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}

}
