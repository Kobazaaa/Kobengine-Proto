#--------------------------------------------------
#    Kobengine CMake
#--------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Kobengine)

set(ENGINE_NAME kobengine)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Kobengine)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

# list source files here
add_library(${ENGINE_NAME} STATIC
  # Main/
  "${SOURCE_DIR}/Main/main.cpp"
  "${SOURCE_DIR}/Main/Kobengine.cpp"
  "${SOURCE_DIR}/Main/Kobengine.h"

  # Engine/
  "${SOURCE_DIR}/Engine/SpriteSheet.cpp"
  "${SOURCE_DIR}/Engine/SpriteSheet.h"
  "${SOURCE_DIR}/Engine/Font.cpp"
  "${SOURCE_DIR}/Engine/Font.h"
  "${SOURCE_DIR}/Engine/Renderer.cpp"
  "${SOURCE_DIR}/Engine/Renderer.h"
  "${SOURCE_DIR}/Engine/Scene.cpp"
  "${SOURCE_DIR}/Engine/Scene.h"
  "${SOURCE_DIR}/Engine/Texture2D.cpp"
  "${SOURCE_DIR}/Engine/Texture2D.h"
  "${SOURCE_DIR}/Engine/Timer.h"
  "${SOURCE_DIR}/Engine/Timer.cpp"
  "${SOURCE_DIR}/Engine/ServiceLocator.h"
    # Engine/Managers/
  "${SOURCE_DIR}/Engine/Managers/InputManager.cpp"
  "${SOURCE_DIR}/Engine/Managers/InputManager.h"
  "${SOURCE_DIR}/Engine/Managers/ResourceManager.cpp"
  "${SOURCE_DIR}/Engine/Managers/ResourceManager.h"
  "${SOURCE_DIR}/Engine/Managers/SceneManager.cpp"
  "${SOURCE_DIR}/Engine/Managers/SceneManager.h"
    # Engine/Input/
  "${SOURCE_DIR}/Engine/Input/Gamepad.cpp"
  "${SOURCE_DIR}/Engine/Input/Gamepad.h"
    # Engine/Audio/
  "${SOURCE_DIR}/Engine/Audio/ISoundSystem.h"
  "${SOURCE_DIR}/Engine/Audio/SDLSoundSystem.h"
  "${SOURCE_DIR}/Engine/Audio/SDLSoundSystem.cpp"
  "${SOURCE_DIR}/Engine/Audio/LoggerSoundSystem.h"
  "${SOURCE_DIR}/Engine/Audio/LoggerSoundSystem.cpp"
  "${SOURCE_DIR}/Engine/Audio/NullSoundSystem.h"
    # Engine/Collision/
  "${SOURCE_DIR}/Engine/Collision/ICollisionSystem.h"
  "${SOURCE_DIR}/Engine/Collision/NullCollisionSystem.h"

  #../ Object/
  "${SOURCE_DIR}/Object/GameObject.cpp"
  "${SOURCE_DIR}/Object/GameObject.h"
  "${SOURCE_DIR}/Object/Transform.cpp"
  "${SOURCE_DIR}/Object/Transform.h"
  "${SOURCE_DIR}/Object/Component.h"
  "${SOURCE_DIR}/Object/Component.cpp"
  "${SOURCE_DIR}/Object/Command.h"

  #../ Events/
  "${SOURCE_DIR}/Events/EventListeners.h"
  "${SOURCE_DIR}/Events/Event.h"

  #../ Components/
  "${SOURCE_DIR}/Components/ColliderComponent.h"
  "${SOURCE_DIR}/Components/ColliderComponent.cpp"
  "${SOURCE_DIR}/Components/GridRendererComponent.h"
  "${SOURCE_DIR}/Components/GridRendererComponent.cpp"
  "${SOURCE_DIR}/Components/TextRendererComponent.h"
  "${SOURCE_DIR}/Components/TextRendererComponent.cpp"
  "${SOURCE_DIR}/Components/ImageRendererComponent.h"
  "${SOURCE_DIR}/Components/ImageRendererComponent.cpp"
  "${SOURCE_DIR}/Components/FPSComponent.h"
  "${SOURCE_DIR}/Components/FPSComponent.cpp"
  "${SOURCE_DIR}/Components/IntUIComponent.h"
  "${SOURCE_DIR}/Components/IntUIComponent.cpp"
  "${SOURCE_DIR}/Components/Animator.cpp"
  "${SOURCE_DIR}/Components/Animator.h"
)

# enable c++20 features
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_20)

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

# add SDL2
if (WIN32)
  FetchContent_Declare(
    SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.30.10-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 
  )
  FetchContent_GetProperties(SDL2)
  if(NOT SDL2_POPULATED)
    FetchContent_Populate(SDL2)
    set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
  else()
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
  endif()
  endif()

  # add SDL2_image
  FetchContent_Declare(
    SDL2_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.3-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_image)
  if(NOT SDL2_image_POPULATED)
    FetchContent_Populate(SDL2_image)
    set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
  else()
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
  endif()
  endif()

  # add SDL2_ttf
  FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.22.0-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_ttf)
  if(NOT sdl2_ttf_POPULATED)
    FetchContent_Populate(SDL2_ttf)
    set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
  else()
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
  endif()
  endif()

  # add SDL2_mixer
  FetchContent_Declare(
    SDL2_mixer
    URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-devel-2.8.1-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL_mixer)
  if(NOT SDL2_mixer_POPULATED)
    FetchContent_Populate(SDL2_mixer)
    set(SDL2_MIXER_INCLUDE_DIR ${sdl2_mixer_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_MIXER_LIBRARIES ${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.lib)
    set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.dll")
  else()
    set(SDL2_MIXER_LIBRARIES ${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.lib)
    set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.dll")
  endif()
  endif()

  find_package(VLD CONFIG)

  # set all include directories
  target_include_directories(${ENGINE_NAME} PUBLIC
    ${VLD_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
  )
  
  # set libraries to link with
  target_link_libraries(${ENGINE_NAME} PUBLIC Xinput
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    ${VLD_LIBRARY}
  )
else()

  FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.10
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL2)
  
  FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2IMAGE_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_image)

  FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2TTF_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_ttf)

  FetchContent_Declare(
    SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDLMIXER_INSTALL OFF)
  FetchContent_MakeAvailable(SDL_mixer)

  target_include_directories("${ENGINE_NAME}" PUBLIC 
    ${sdl2_SOURCE_DIR}/include
    ${sdl2_image_SOURCE_DIR}/include
    ${sdl2_ttf_SOURCE_DIR}
    ${sdl2_mixer_SOURCE_DIR}
  )
  target_link_libraries("${ENGINE_NAME}" PUBLIC 
    SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL_mixer::SDL_mixer
  )
endif()

# add ImGui
FetchContent_Declare(
  imgui
  URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b-docking.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)
FetchContent_MakeAvailable(imgui)

# add ImPlot
FetchContent_Declare(
  implot
  URL https://github.com/epezent/implot/archive/refs/tags/v0.16.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)
FetchContent_MakeAvailable(implot)

# Add the ImGui sources to project
target_sources(${ENGINE_NAME} PRIVATE
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# Add the ImPlot sources to project
target_sources(${ENGINE_NAME} PRIVATE
  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp
)

target_include_directories(${ENGINE_NAME} PUBLIC
  ${SOURCE_DIR}
  ${SOURCE_DIR}/Commands
  ${SOURCE_DIR}/Components
  ${SOURCE_DIR}/Engine
  ${SOURCE_DIR}/Engine/Managers
  ${SOURCE_DIR}/Engine/Input
  ${SOURCE_DIR}/Engine/Audio
  ${SOURCE_DIR}/Engine/Collision
  ${SOURCE_DIR}/Main
  ${SOURCE_DIR}/Object
  ${SOURCE_DIR}/Events

  ${glm_SOURCE_DIR}

  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends

  ${implot_SOURCE_DIR}
)

# compile at max warning level + treat warnings as errors
target_compile_options(${ENGINE_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(WIN32)
  set_target_properties(${ENGINE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${ENGINE_NAME}>")

  # add post build commands
  add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${ENGINE_NAME}>"
  )
  add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${ENGINE_NAME}>"
  )
  add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${ENGINE_NAME}>"
  )
  add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_MIXER_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${ENGINE_NAME}>"
  )
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
  add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/assets/" "$<TARGET_FILE_DIR:${ENGINE_NAME}>/assets/"
      COMMENT "Copying assets"
  )
else()
    message(WARNING "Assets directory not found. Skipping copy.")
endif()
