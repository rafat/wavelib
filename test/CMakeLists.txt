add_executable(cwttest cwttest.c)

target_link_libraries(cwttest wavelib)

add_executable(dwttest dwttest.c)

target_link_libraries(dwttest wavelib)

add_executable(swttest swttest.c)

target_link_libraries(swttest wavelib)

add_executable(modwttest modwttest.c)

target_link_libraries(modwttest wavelib)

add_executable(dwpttest dwpttest.c)

target_link_libraries(dwpttest wavelib)

add_executable(wtreetest wtreetest.c)

target_link_libraries(wtreetest wavelib)

add_executable(denoisetest denoisetest.c)

target_link_libraries(denoisetest wauxlib wavelib)

add_executable(modwtdenoisetest modwtdenoisetest.c)

target_link_libraries(modwtdenoisetest wauxlib wavelib)

add_executable(dwt2test dwt2test.c)

target_link_libraries(dwt2test wavelib)

add_executable(swt2test swt2test.c)

target_link_libraries(swt2test wavelib)

add_executable(modwt2test modwt2test.c)

target_link_libraries(modwt2test wavelib)

set_target_properties(cwttest dwttest swttest modwttest dwpttest wtreetest denoisetest modwtdenoisetest dwt2test swt2test modwt2test
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/test"
        )
