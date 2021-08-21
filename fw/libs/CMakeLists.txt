# file(GLOB_RECURSE SOURCES *.c)
# idf_component_register(SRCS "${SOURCES}"
#                        INCLUDE_DIRS ".")

file(GLOB_RECURSE SRC_FSM amg8833/amg8833.c)

set(SOURCES ${SRC_FSM} ${SRC_ZMOD})

idf_component_register(SRCS "${SOURCES}"
                       INCLUDE_DIRS ".")
