#pragma once

// CMakeLists.txt reads the version from these three lines: keep them in this format.
// NOLINTBEGIN(modernize-macro-to-enum)
#define RCLI_VERSION_MAJOR 2
#define RCLI_VERSION_MINOR 1
#define RCLI_VERSION_PATCH 0
// NOLINTEND(modernize-macro-to-enum)

#define RCLI_STRINGIFY_IMPL(x) #x
#define RCLI_STRINGIFY(x) RCLI_STRINGIFY_IMPL(x)

#define RCLI_VERSION                   \
	RCLI_STRINGIFY(RCLI_VERSION_MAJOR) \
	"." RCLI_STRINGIFY(RCLI_VERSION_MINOR) "." RCLI_STRINGIFY(RCLI_VERSION_PATCH)
