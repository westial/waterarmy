project(gmock-global)

set(HEADER_FILES
        include/gmock-global/gmock-global.h)

add_library(gmock-global STATIC ${HEADER_FILES})

set_target_properties(gmock-global PROPERTIES LINKER_LANGUAGE CXX)