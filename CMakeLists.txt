cmake_minimum_required(VERSION 3.15)

project(naturec C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Quiet down raylib's own examples/tests; we only want the library.
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/raylib)
add_subdirectory(deps/box2d)

# ----------------------------------------------------------------------------
# Optional shared helper library.
#
# As you translate Nature of Code you'll build reusable pieces (PVector, Mover,
# Walker, etc.). Drop them in common/ and they get compiled into the `nature`
# library and linked into every example automatically.
# ----------------------------------------------------------------------------
file(GLOB COMMON_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/common/*.c)
if(COMMON_SOURCES)
    add_library(nature STATIC ${COMMON_SOURCES})
    target_include_directories(nature PUBLIC ${CMAKE_SOURCE_DIR}/common)
    target_link_libraries(nature PUBLIC raylib)
endif()

# ----------------------------------------------------------------------------
# Auto-discover examples.
#
# Every chap*/<name>.c becomes its own executable, named <chapter>_<name>
# (e.g. chap0_example01) and written to build/bin/<chapter>/<name>.
# Add a new .c file and re-run the build -- no edits needed here.
# ----------------------------------------------------------------------------
file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/chap*/*.c)

foreach(src ${EXAMPLE_SOURCES})
    get_filename_component(chapter ${src} DIRECTORY)
    get_filename_component(chapter ${chapter} NAME)   # e.g. chap0
    get_filename_component(name ${src} NAME_WE)       # e.g. example01
    set(target ${chapter}_${name})

    add_executable(${target} ${src})
    target_link_libraries(${target} raylib)
    if(TARGET nature)
        target_link_libraries(${target} nature)
    endif()

    # Only link Box2D into examples that actually include its header.
    file(READ ${src} src_contents)
    if(src_contents MATCHES "#[ \t]*include[ \t]*[<\"](box2d/)?box2d\\.h[>\"]")
        target_link_libraries(${target} box2d)
    endif()

    set_target_properties(${target} PROPERTIES
        OUTPUT_NAME ${name}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${chapter})
endforeach()
