cmake_minimum_required (VERSION 2.8.11)
project("PMC Wolfenstein3D")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# if("${BUILD_SHARED_LIBS}" STREQUAL "ON")
#   string(REPLACE "/MTd" "/MDd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
#   string(REPLACE "/MT" "/MD" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
# else()
#   string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
#   string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
# endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "/imsvc ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  --driver-mode=cl -fms-compatibility-version=19")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror\
#  -Wno-c++98-compat -Wno-c++98-compat-pedantic\
#  -Wno-c++98-c++11-compat-pedantic -Wno-undefined-internal\
#  -Wno-exit-time-destructors -Wno-global-constructors\
#  -Wno-unknown-pragmas -Wno-missing-prototypes -Wno-undef\
#  -Wno-language-extension-token -Wno-missing-noreturn -Wno-missing-noreturn\
#  -Wno-language-extension-token -Wno-used-but-marked-unused\
#  -Wno-shift-sign-overflow -Wno-deprecated -Wno-documentation-deprecated-sync\
#  -Wno-weak-vtables -Wno-sign-conversion -Wno-padded -Wno-covered-switch-default\
#  -Wno-extra-semi -Wno-shadow-field-in-constructor -Wno-missing-variable-declarations")

add_executable(wolf
  src/core/Camera.cpp
  src/core/Graphics.cpp
  src/core/Main.cpp
  src/core/Objectclass.cpp
  )
set_target_properties(wolf PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
target_link_libraries(wolf gdi32 user32 glu32 opengl32)
add_custom_command(TARGET wolf POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/src/textures $<TARGET_FILE_DIR:wolf>/textures)
