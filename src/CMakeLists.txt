

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES    conv.c
					hsfft.c
					real.c
					wavefilt.c
					wavelib.c
					wtmath.c
                    )

set(HEADER_FILES    conv.h
					hsfft.h
					real.h
					wavefilt.h
					wavelib.h
					wtmath.h
                    )

add_library(wavelib STATIC ${SOURCE_FILES} ${HEADER_FILES})
        
set_property(TARGET wavelib PROPERTY FOLDER "lib")

target_include_directories(wavelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

