cmake_minimum_required(VERSION 3.28.3)
project(MyGame VERSION 0.1.0 LANGUAGES C)

# Create your executable
add_executable(${PROJECT_NAME} src/main.c)


include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    )
FetchContent_MakeAvailable(raylib)
    
# Link raylib to your executable
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Optional: Configure raylib build options (e.g., disable examples)
#set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE)

# Define the source assets directory
set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

# Define the destination assets directory in the build folder
set(ASSETS_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

# Create a custom target to copy the assets
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SOURCE_DIR}" "${ASSETS_BUILD_DIR}"
    COMMENT "Copying assets to build directory"
)

# Ensure the assets are copied before your main target is built
add_dependencies(${PROJECT_NAME} copy_assets)
