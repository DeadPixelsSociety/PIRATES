set(DOXYFILE ${CMAKE_SOURCE_DIR}/doc/doxyfile)

configure_file(${DOXYFILE} doxyfile.cmake @ONLY)

add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} doxyfile.cmake)
