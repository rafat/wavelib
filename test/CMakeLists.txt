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

if(UNIX)
	target_link_libraries(cwttest m)
	target_link_libraries(dwttest m)
	target_link_libraries(swttest m)
	target_link_libraries(modwttest m)
	target_link_libraries(dwpttest m)
	target_link_libraries(wtreetest m)
	target_link_libraries(denoisetest m)
endif()

set_target_properties(cwttest dwttest swttest modwttest dwpttest wtreetest denoisetest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/test"
        )
