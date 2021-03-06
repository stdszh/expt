if (NOT DEFINED __COMMON_INCLUDE__)

set(__COMMON_INCLUDE__ 1)

set(COMMON_INCLUDE_DIR ${CMAKE_BINARY_DIR}/include/common)
set(COMMON_LIBRARY_DIR ${CMAKE_BINARY_DIR}/lib/common)
set(COMMON_BINRARY_DIR ${CMAKE_BINARY_DIR}/bin/common)
set(COMMON_LIBS common)

set(MODULE_INCLUDE_DIR ${MODULE_INCLUDE_DIR} ${COMMON_INCLUDE_DIR})
set(MODULE_LIBRARY_DIR ${MODULE_LIBRARY_DIR} ${COMMON_LIBRARY_DIR})
set(MODULE_LIBS ${MODULE_LIBS} ${COMMON_LIBS})

endif (NOT DEFINED __COMMON_INCLUDE__)