add_library(
	storeLib
	store.cpp
	store.h
	utility.cpp
	utility.h
	tests.cpp
	tests.h
)

target_compile_definitions(
	storeLib
	PRIVATE
		$<$<CONFIG:Debug>:DEBUG>
		$<$<CONFIG:Release>:RELEASE>
)

target_compile_options(
	storeLib
	PRIVATE
		${DEFAULT_COMPILER_OPTIONS}
)

target_link_options(
	storeLib
	PRIVATE
		${DEFAULT_LINKER_OPTIONS}
)
