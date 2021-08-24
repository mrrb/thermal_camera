# file(GLOB_RECURSE SOURCES *.c)
# idf_component_register(SRCS "${SOURCES}"
#                        INCLUDE_DIRS ".")

file(GLOB_RECURSE SRC_FSM amg88/amg88.c)

set(SOURCES ${SRC_FSM} ${SRC_ZMOD})

idf_component_register(SRCS "${SOURCES}"
                       INCLUDE_DIRS ".")
