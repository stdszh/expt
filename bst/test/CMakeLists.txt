include(bst)

include_directories(${MODULE_INCLUDE_DIR})
link_directories(${MODULE_LIBRARY_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)

add_executable(bst_test ${SOURCES})
target_link_libraries(bst_test PUBLIC ${MODULE_LIBS})