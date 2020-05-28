

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES    conv.c
					cwt.c
					cwtmath.c
					hsfft.c
					real.c
					wavefilt.c
					wavefunc.c
					wavelib.c
					wtmath.c
                    )

set(HEADER_FILES    conv.h
					cwt.h
					cwtmath.h
					hsfft.h
					real.h
					wavefilt.h
					wavefunc.h
					wtmath.h
                    )

add_library(wavelib STATIC ${SOURCE_FILES} ${HEADER_FILES})

include(CheckSymbolExists)

# https://stackoverflow.com/questions/32816646/can-cmake-detect-if-i-need-to-link-to-libm-when-using-pow-in-c
if(NOT POW_FUNCTION_EXISTS AND NOT NEED_LINKING_AGAINST_LIBM)
    check_symbol_exists(pow "math.h" POW_FUNCTION_EXISTS)
    if(NOT POW_FUNCTION_EXISTS)
        unset(POW_FUNCTION_EXISTS CACHE)
        list(APPEND CMAKE_REQUIRED_LIBRARIES m)
        check_symbol_exists(pow "math.h" POW_FUNCTION_EXISTS)
        if(POW_FUNCTION_EXISTS)
            set(NEED_LINKING_AGAINST_LIBM True CACHE BOOL "" FORCE)
        else()
            message(FATAL_ERROR "Failed making the pow() function available")
        endif()
    endif()
endif()

if(NEED_LINKING_AGAINST_LIBM)
    target_link_libraries(wavelib PUBLIC m)
endif()

set_property(TARGET wavelib PROPERTY FOLDER "lib")

target_include_directories(wavelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}../header)

install(TARGETS wavelib
    EXPORT wavelib-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT wavelib-targets
    FILE wavelib-config.cmake
    NAMESPACE wavelib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/wavelib)
