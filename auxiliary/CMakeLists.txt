include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES denoise.c
)

set(HEADER_FILES denoise.h
)

add_library(denoiselib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(denoiselib wavelib)

set_property(TARGET denoiselib PROPERTY FOLDER "lib")

target_include_directories(denoiselib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

