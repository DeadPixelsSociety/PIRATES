file(GLOB LIB_CLIENT_SRC "*.cpp")

add_library(libClient STATIC ${LIB_CLIENT_SRC})

target_link_libraries(libClient ${SFML2_LIBRARIES} ${LIBTMX_LIBRARIES})


