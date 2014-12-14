file(GLOB LIB_SERVER_SRC "*.cpp")

add_library(libServer SHARED ${LIB_SERVER_SRC})

target_link_libraries(libServer ${SFML2_LIBRARIES} ${BOX2D_LIBRARIES})


