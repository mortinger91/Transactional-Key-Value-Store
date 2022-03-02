add_executable (
	store main.cpp
)

target_compile_definitions(
	store
	PRIVATE
		$<$<CONFIG:Debug>:DEBUG>
		$<$<CONFIG:Release>:RELEASE>
)

target_compile_options(
	store
	PRIVATE
		${DEFAULT_COMPILER_OPTIONS}
)

target_link_options(
	store
	PRIVATE
		${DEFAULT_LINKER_OPTIONS}
)

target_link_libraries (
	store
	storeLib
	${PLATFORM_LIBS}
)
