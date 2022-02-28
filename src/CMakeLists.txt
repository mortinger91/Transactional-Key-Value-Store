add_library(
	${LIBRARY_TARGET_NAME}
	STATIC
	store.cpp
	store.h
)

target_include_directories(
	${LIBRARY_TARGET_NAME}
	PUBLIC
	"src"
)

target_compile_definitions(
	${LIBRARY_TARGET_NAME}
	PRIVATE
	$<$<CONFIG:Debug>:DEBUG>
	$<$<CONFIG:Release>:RELEASE>
)

target_compile_options(
	${LIBRARY_TARGET_NAME}
	PUBLIC
	${DEFAULT_COMPILER_OPTIONS}
)

target_link_options(
	${LIBRARY_TARGET_NAME}
	PRIVATE
	${DEFAULT_LINKER_OPTIONS}
)
