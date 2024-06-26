#---------------------------------------------------------------------------------------------------
# CMake Build Configuration for the Ray Tracing Weekend Series
#
# See README.md for guidance.
#---------------------------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.1.0...3.27.0 )

project ( RTWeekend LANGUAGES CXX )

# Set to C++11
set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

# Source

set ( EXTERNAL
  src/external/stb_image.h
  src/external/log.h
  src/external/progressbar.h
  src/external/params.h
)

set ( SOURCE
src/external/stb_image.h
src/external/log.h
src/external/progressbar.h
src/external/params.h

src/camera.h
src/color.h
src/hittable.h
src/hittable_list.h
src/interval.h
src/material.h
src/ray.h
src/rtw_stb_image.h
src/rtweekend.h
src/sphere.h
src/vec3.h
src/aabb.h
src/bvh.h
src/constant_medium.h
src/perlin.h
src/quad.h
src/texture.h
src/onb.h
src/pdf.h

src/main.cc
)

include_directories(src)

# Specific compiler flags below. We're not going to add options for all possible compilers, but if
# you're new to CMake (like we are), the following may be a helpful example if you're using a
# different compiler or want to set different compiler options.

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/we 4265") # Class has virtual functions, but its non-trivial destructor is not virtual
    add_compile_options("/w3 5038") # Data member will be initialized after [other] data member
    add_compile_options("/we 5204") # Class has virtual functions, but its trivial destructor is not virtual
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wmaybe-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wsometimes-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
endif()

# Executables
add_executable(main     ${EXTERNAL} ${SOURCE})
add_executable(cos_cubed         src/cos_cubed.cc         )
add_executable(cos_density       src/cos_density.cc       )
add_executable(integrate_x_sq    src/integrate_x_sq.cc    )
add_executable(pi                src/pi.cc                )
add_executable(estimate_halfway  src/estimate_halfway.cc  )
add_executable(sphere_importance src/sphere_importance.cc )
add_executable(sphere_plot       src/sphere_plot.cc       )