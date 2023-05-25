add_executable(blockKiller)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.h)
target_sources(blockKiller PRIVATE ${SOURCE_FILES})
target_link_libraries(blockKiller sfml-system sfml-window sfml-graphics sfml-audio)
