                                
set(SOURCE_FILES
		tst_dwt.cpp
		BoostTest.cpp
	)
	
set(HEADER_FILES
	BoostTest.h
	)





add_executable(wavelibLibTests ${SOURCE_FILES} ${HEADER_FILES})

add_test(NAME wavelibLibTests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test  COMMAND wavelibLibTests)

include_directories(${BOOST_DIR})
add_dependencies(wavelibLibTests wavelib)
target_link_libraries(wavelibLibTests ${Boost_LIBRARIES}
									    wavelib)

target_include_directories(wavelibLibTests PUBLIC
							${CMAKE_SOURCE_DIR}/../../header
                            ${Boost_INCLUDE_DIR}
							)
                            
target_compile_definitions(wavelibLibTests PUBLIC BOOST_ALL_NO_LIB UNIT_TEST)


install(TARGETS wavelibLibTests
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION tests
    ARCHIVE DESTINATION tests
    )