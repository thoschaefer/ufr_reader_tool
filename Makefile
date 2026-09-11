# macOS build for uFR_Readers_tool.
# The .cbp project targets Windows/MinGW only; this Makefile builds the same
# sources natively on macOS against wxWidgets (Cocoa) and the bundled
# ufr-lib/macos uFCoder library.
#
# Prerequisites: Xcode Command Line Tools, wxWidgets (e.g. `brew install wxwidgets@3.2`).

WX_CONFIG := $(shell command -v wx-config-3.2 2>/dev/null || command -v wx-config 2>/dev/null)
ifeq ($(WX_CONFIG),)
$(error wx-config not found. Install wxWidgets, e.g. `brew install wxwidgets@3.2`)
endif

CXX ?= clang++
UFCODER_DIR := ufr-lib/macos/universal
UFCODER_LIB := uFCoder-macos
UFCODER_LDFLAGS := -L$(UFCODER_DIR) -l$(UFCODER_LIB) -Wl,-rpath,@executable_path/../../$(UFCODER_DIR)

CXXFLAGS := -std=c++17 -O2 -Wall -Iufr-lib/include $(shell $(WX_CONFIG) --cxxflags)
LDFLAGS  := $(UFCODER_LDFLAGS) $(shell $(WX_CONFIG) --libs)

BINDIR   := bin/macos
TARGET   := $(BINDIR)/uFR_Readers_tool
SOURCES  := uFR_Readers_toolApp.cpp uFR_Readers_toolMain.cpp
OBJECTS  := $(SOURCES:%.cpp=$(BINDIR)/%.o)

LED_TARGET := $(BINDIR)/led_off

.PHONY: all run clean led-off run-led-off

all: $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%.o: %.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

run: $(TARGET)
	./$(TARGET)

# One-shot CLI to turn off the reader's idle-blink and card-detection LEDs
# (uFR Zero series only). The setting is stored in the reader's EEPROM, so
# it only needs to be run once and survives power cycles.
led-off: $(LED_TARGET)

$(LED_TARGET): $(BINDIR)/led_off.o
	$(CXX) $< $(UFCODER_LDFLAGS) -o $@

run-led-off: $(LED_TARGET)
	./$(LED_TARGET)

clean:
	rm -rf $(BINDIR)
