#include "RenderCommand.h"
#include "Core/Base.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLrendererAPI.h"

namespace Engine {

Scope<RendererAPI> RenderCommand::s_RendererAPI = createScope<OpenGLrendererAPI>();

}
