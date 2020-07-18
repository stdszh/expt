if (NOT DEFINED __BST_INCLUDE__)

set(__BST_INCLUDE__ 1)

include(common)

set(BST_INCLUDE_DIR ${CMAKE_BINARY_DIR}/include/bst)
set(BST_LIBRARY_DIR ${CMAKE_BINARY_DIR}/lib/bst)
set(BST_BINRARY_DIR ${CMAKE_BINARY_DIR}/bin/bst)
set(BST_LIBS bst)

set(MODULE_INCLUDE_DIR ${MODULE_INCLUDE_DIR} ${BST_INCLUDE_DIR})
set(MODULE_LIBRARY_DIR ${MODULE_LIBRARY_DIR} ${BST_LIBRARY_DIR})
set(MODULE_LIBS ${MODULE_LIBS} ${BST_LIBS})

endif (NOT DEFINED __BST_INCLUDE__)