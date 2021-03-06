CC                = clang
CFLAGS            = -Wall
LDFLAGS           = -c
VPATH             = src src/core src/tests
LIBS              = 
SDL_FLAGS         = `sdl-config --cflags --libs`

TEST_CFLAGS       = --coverage $(CFLAGS)
TEST_LIBS         = -lprofile_rt

LCOV_FLAGS        = -c -b ./ -d ./

MAIN_BUILD_DIR    = build/main
TEST_BUILD_DIR    = build/tests
HEADER_DIRS       = include
COVERAGE_DIR      = coverage
COVERAGE_FILE     = $(COVERAGE_DIR)/coverage.info

INCLUDES          = $(addprefix -I, $(HEADER_DIRS))

CORE_SOURCES      = $(notdir $(wildcard src/core/*.c))
TEST_SOURCES      = $(notdir $(wildcard src/tests/*.c)) $(CORE_SOURCES)
MAIN_SOURCES      = main.c $(CORE_SOURCES)

MAIN_OBJECTS      = $(addprefix $(MAIN_BUILD_DIR)/, $(MAIN_SOURCES:.c=.o))
TEST_OBJECTS      = $(addprefix $(TEST_BUILD_DIR)/, $(TEST_SOURCES:.c=.o))

EXECUTABLE        = conway
TEST_EXECUTABLE   = $(addprefix $(TEST_BUILD_DIR)/, test_$(EXECUTABLE))

all: $(EXECUTABLE)

tests: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

coverage: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)
	lcov $(LCOV_FLAGS) -o $(COVERAGE_FILE)
	lcov -r $(COVERAGE_FILE) test\* -o $(COVERAGE_FILE)
	genhtml $(COVERAGE_FILE) -o $(COVERAGE_DIR)

$(MAIN_BUILD_DIR)/%.o: %.c
	$(CC) $(LDFLAGS) $(CFLAGS) $(INCLUDES) $< -o $@

$(TEST_BUILD_DIR)/%.o: %.c
	$(CC) $(LDFLAGS) $(TEST_CFLAGS) $(INCLUDES) $< -o $@

$(EXECUTABLE): $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) $(MAIN_OBJECTS) $(SDL_FLAGS) -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(TEST_LIBS) $(TEST_CFLAGS) $(TEST_OBJECTS) $(SDL_FLAGS) -o $@

clean:
	rm -rf $(MAIN_BUILD_DIR)/* $(EXECUTABLE)
	rm -rf $(TEST_BUILD_DIR)/*

