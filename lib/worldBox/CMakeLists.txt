file(GLOB LIB_WORLDBOX_SRC "*.cpp")

add_library(libWorldBox SHARED ${LIB_WORLDBOX_SRC})

target_link_libraries(libWorldBox ${BOX2D_LIBRARIES} ${SFML2_LIBRARIES})


