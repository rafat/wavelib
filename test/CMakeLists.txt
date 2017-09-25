add_executable(cwttest cwttest.c)

target_link_libraries(cwttest wavelib m)

add_executable(dwttest dwttest.c)

target_link_libraries(dwttest wavelib m)

add_executable(swttest swttest.c)

target_link_libraries(swttest wavelib m)

add_executable(modwttest modwttest.c)

target_link_libraries(modwttest wavelib m)

add_executable(dwpttest dwpttest.c)

target_link_libraries(dwpttest wavelib m)

add_executable(wtreetest wtreetest.c)

target_link_libraries(wtreetest wavelib m)

add_executable(denoisetest denoisetest.c)

target_link_libraries(denoisetest wauxlib wavelib m)

set_target_properties(cwttest dwttest swttest modwttest dwpttest wtreetest denoisetest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/test"
        )