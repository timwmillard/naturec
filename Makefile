BUILD := build

# Which example `make run` launches. Override on the command line, e.g.
#   make run EX=chap0/example01
EX ?= chap0/example01

.PHONY: all build configure run list clean

all: build

# Configure once; CMake re-runs itself when CMakeLists.txt or the set of
# source files changes (CONFIGURE_DEPENDS).
$(BUILD)/CMakeCache.txt:
	@cmake -B $(BUILD) -DCMAKE_BUILD_TYPE=Debug

configure: $(BUILD)/CMakeCache.txt

build: configure
	@cmake --build $(BUILD)

# Build everything, then run the selected example.
run: build
	@./$(BUILD)/bin/$(EX)

# List every example target CMake knows about.
list: configure
	@cmake --build $(BUILD) --target help | grep -E '^\.\.\. chap' || true

clean:
	@rm -rf $(BUILD)
