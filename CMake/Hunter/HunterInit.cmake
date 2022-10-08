include_guard()

include(${CMAKE_CURRENT_LIST_DIR}/HunterGate.cmake)

HunterGate(
	URL "https://github.com/cpp-pm/hunter/archive/v0.24.1.tar.gz"
	SHA1 "4942227a6e6f5e64414c55b97ef98609de199d18"
	FILEPATH "${CMAKE_CURRENT_LIST_DIR}/HunterConfig.cmake"
)
