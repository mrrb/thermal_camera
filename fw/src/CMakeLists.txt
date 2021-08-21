file(GLOB_RECURSE SOURCES *.c)

idf_component_register(SRCS "${SOURCES}"
                       INCLUDE_DIRS ""
                       REQUIRES libs include spi_flash nvs_flash)

# idf_component_register(SRCS "main.c"
#                        INCLUDE_DIRS ""
#                        REQUIRES libs include spi_flash)
