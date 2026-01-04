# =====================================
# use 4 spaces for TAB to read properly
# =====================================

# --------- makefile rules ------------
# 1. `ifneq`, `else`, `endif`, `$(1)`, `$(error)`, `$_FOO`, and `TARGET:`
#    can have optional preceding spaces, but no tabs
# 2. SHELL command must have preceding [tab]+
# 3. # comment can have either preceding [tab]+ or spaces

# -----------------------------------------------------------------------------
# Tools
# -----------------------------------------------------------------------------
SDAS      := sdasz80
SDCC      := sdcc
SDAR      := sdar
SDOBJCOPY := sdobjcopy
Z80DASM   := z80dasm

ASMFLAGS  := -l
CFLAGS    := -mz80 --std c99 -I_headers --Werror
# COPTFLAGS := --no-peep --nooverlay --nogcse --nolospre --nogenconstprop --nolabelopt --noinvariant --noinduction --noloopreverse --nostdlibcall
COPTFLAGS :=
LDFLAGS   := -mz80 --no-std-crt0
DASMFLAGS := -a -l -t -g0

GREP := grep -E
RM   := rm -f
CP   := cp

TIMESTAMP_CMD := env TZ="Asia/Bangkok" date "+%Y-%m-%d %H_%M_%S %z"

CODE_DIR := /BareMetal-C/code

# List of folders to ignore (space separated, relative to BareMetal-C/code/)
# e.g. EXCLUDED_DIRS := _instructor/_problem_matcher_tests folder_b folder_c
EXCLUDED_DIRS := _instructor/_problem_matcher_tests .obsolete

# -----------------------------------------------------------------------------
# Argument Processing
# -----------------------------------------------------------------------------
# Set Defaults
#    If RECURSE is undefined, use 1
RECURSE ?= 1

#    If DIR is undefined, use 'foo/BareMetal-C/code'
ifndef DIR
    RAW_DIR := $(abspath .)
else
    # Also use abspath here in case the user passes "." or relative paths
    RAW_DIR := $(abspath $(DIR))
endif

# Sanitize DIR (replace backslashes with forward slashes)
RAW_DIR2 := $(subst \,/,$(RAW_DIR))

# Regex: match (something)?/BareMetal-C/code followed by end-of-string ($) or a slash (/)
#    Note: '.*?' is non-greedy match to handle long paths correctly.
FIXED_DIR := $(shell echo '$(RAW_DIR2)' | perl -ne 'if(s|.*?/BareMetal-C/code/*|/BareMetal-C/code/|){ s|/$$||; print; }')

# 2. Check: If FIXED_DIR is empty, the Perl regex failed to match.
ifeq ($(FIXED_DIR),)
    $(info RAW_DIR2 = $(RAW_DIR2))
    $(error [ERROR] Invalid Path! Must contain '/BareMetal-C/code')
endif

STRIPPED_DIR := $(shell echo '$(FIXED_DIR)' | perl -pe 's#.*(?:/BareMetal-C|/BareMetal-C)/code/?##; s#^/##; s#^/##; s#/*$$##')

# 3. Echo resolved values
# $(info RAW_DIR      = $(RAW_DIR))
# $(info RAW_DIR2     = $(RAW_DIR2))
$(info FIXED_DIR    = $(FIXED_DIR))
$(info STRIPPED_DIR = $(STRIPPED_DIR))
$(info RECURSE      = $(RECURSE))
$(info EXLUDED_DIRS = $(EXCLUDED_DIRS))

# -----------------------------------------------------------------------------
# Discovery & Target Selection
# -----------------------------------------------------------------------------

# CASE 1: Root Context (DIR was empty or just .../BareMetal-C/code)
ifeq ($(STRIPPED_DIR),)
    
    # If RECURSE=0, build the Root Project only (./main.c)
    ifeq ($(RECURSE),0)
        ALL_DIRS := .
    
    # If RECURSE=1, find all sub-projects (p1, p2...), excluding Root (.)
    else
        # Generate prune flags from EXCLUDED_DIRS: turns "foo bar" into '-o -path "./foo" -o -path "./bar"'
        EXCLUDED_FLAGS := $(foreach dir,$(EXCLUDED_DIRS),-o -path "./$(dir)")

        # 1. Find ALL directories recursively, ignoring:
        #    - Any folder starting with "." (like .git, .vscode)
        #    - "_defaults" folder
        #    - "_headers" folder
        #    - "_library" folder
        #    - root "." folder itself
        #    - path "./_instructor/_problem_matcher_tests"
        ALL_DIRS := $(shell find . -type d \( \( -name ".*" ! -name "." \) -o -name "_defaults" -o -name "_headers" -o -name "_library" $(EXCLUDED_FLAGS) \) -prune -o -type d ! -name "." -printf "%P\n")
    endif

# CASE 2: Specific Target Context (DIR was .../BareMetal-C/code/bar)
else

    # Verify target exists
    ifeq ($(wildcard $(STRIPPED_DIR)),)
        $(error [ERROR] The target directory '$(STRIPPED_DIR)' does not exist!)
    endif

    # If RECURSE=0, build ONLY that target folder
    # (If you wanted RECURSE=1 to search INSIDE bar, you would add a find command here)
    ALL_DIRS := $(STRIPPED_DIR)

endif

# Debug Output
# $(info --------------------------------)
$(info )
$(info MODE     - RECURSE=$(RECURSE))
$(info TARGET   - $(if $(STRIPPED_DIR),$(STRIPPED_DIR),Root))
$(info BUILDING - $(ALL_DIRS))
# $(info )
# $(info --------------------------------)

# -----------------------------------------------------------------------------
# Target: "all"
# -----------------------------------------------------------------------------
# Builds every folder found
all: $(ALL_DIRS)

# -----------------------------------------------------------------------------
# Defaults Rules (For _defaults folder)
# -----------------------------------------------------------------------------
_defaults/%.rel: _defaults/%.s
	@echo ">> Rebuilding Default ASM: $<"
	$(SDAS) $(ASMFLAGS) -o $@ $<
	@echo ""

_defaults/%.rel: _defaults/%.c
	@echo ">> Rebuilding Default C: $<"
	$(SDCC) $(CFLAGS) -c $< -o $@
	@echo ""

# -----------------------------------------------------------------------------
# Library Rules (For _library folder)
# -----------------------------------------------------------------------------
LIB_NAME    := baremetal.lib
LIB_DIR     := _library
LIB_SRCS    := $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS    := $(patsubst %.c, %.rel, $(LIB_SRCS))
LIB_TARGET  := $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR)/%.rel: $(LIB_DIR)/%.c
	@echo ">> Compiling Library Object: $<"
	$(SDCC) $(CFLAGS) $(COPTFLAGS) -c $< -o $@

$(LIB_TARGET): $(LIB_OBJS)
	@echo ">> Archiving Library: $@"
	@$(RM) $@
	sdar -rc $@ $(LIB_OBJS)
	@echo ""

# -----------------------------------------------------------------------------
# Logic Per Code Folder
# -----------------------------------------------------------------------------
define DEFINE_RUN_RULES

# 0. Folder Name: $(1)
#    Define the stamp file location: same level as the folder
#    Ex: "foo/bar" -> "foo/built-bar.stamp"
#    Ex: "lab01"   -> "./built-lab01.stamp"
$(1)_STAMP := $(dir $(1))built-$(notdir $(1)).stamp

# 1. Sources Check (non-recursive (-maxdepth 1) via 'find')
$(1)_CSRCS   := $$(shell find $(1) -maxdepth 1 -name "*.c")
$(1)_ASRCS   := $$(shell find $(1) -maxdepth 1 -name "*.s")
$(1)_RELSRCS := $$(shell find $(1) -maxdepth 1 -name "*.rel_")

# CHECK: Are there sources?
ifeq ($$($(1)_CSRCS)$$($(1)_ASRCS)$$($(1)_RELSRCS),)

    # --- PATH A: NO SOURCES (Vacuous Success) ---
    .PHONY: $(1)
    $(1):
		@echo "--- $(1) is empty ---"

else

    # --- PATH B: SOURCES EXIST (Build It) ---

    # 1.0A Validation: No `startup*.s` File
    ifneq ($$(wildcard $(1)/startup*.s),)
        $$(error [ERROR] Forbidden file(s) found in $(1): $$(wildcard $(1)/startup*.s). Filenames matching 'startup*.s' are not allowed.)
    endif

    # 1.0B Validation: Prohibit Custom Reset
    ifneq ($$($(1)_ASRCS),)
        $(1)_BAD_RESET := $$(shell $(GREP) "^\s*\.[oO][rR][gG]\s+(0[xX]0+|0+)\b" $$($(1)_ASRCS))
        ifneq ($$($(1)_BAD_RESET),)
            $$(error [ERROR] Custom reset vector found in $(1) sources. no custom reset allowed.)
        endif
    endif

    # 1.1 Convert Source Lists to object lists
    $(1)_COMPILED_RELS := $$(patsubst %.c, %.rel, $$($(1)_CSRCS))
    $(1)_ASM_RELS      := $$(patsubst %.s, %.rel, $$($(1)_ASRCS))
    $(1)_COPIED_RELS   := $$(patsubst %.rel_, %.rel, $$($(1)_RELSRCS))
    
    # 1.2 Compile C sources
    $$($(1)_COMPILED_RELS): %.rel: %.c
		@$$(RM) built-$(1).stamp
		$$(SDCC) $$(CFLAGS) $(COPTFLAGS) -c $$< -o $$@

    # 1.3 Assemble ASM sources
    $$($(1)_ASM_RELS): %.rel: %.s
		@$$(RM) built-$(1).stamp
		$$(SDAS) $$(ASMFLAGS) -o $$@ $$<

    # 1.4 Copy Pre-compiled Objects
    $$($(1)_COPIED_RELS): %.rel: %.rel_ %.lst_
		@$$(RM) built-$(1).stamp
		@$$(CP) $$*.rel_ $$*.rel
		@$$(CP) $$*.lst_ $$*.lst

    # 2. Define All Object Files
    $(1)_ALL_RELS := $$($(1)_COMPILED_RELS) $$($(1)_ASM_RELS) $$($(1)_COPIED_RELS)
    
    # 3. ISR Detection (Perl)
    $(1)_ISR_FOUND := $$(shell perl -ne 'if (/\b_?nmi_handler\b/) { print $$$$ARGV; exit }' $$($(1)_CSRCS) $$($(1)_ASRCS) $$($(1)_RELSRCS) /dev/null)
    
    # 4. HANDLER_OBJ Logic
    ifneq ($$($(1)_ISR_FOUND),)
        $(1)_HANDLER_OBJ := $$(addsuffix .rel, $$(basename $$($(1)_ISR_FOUND)))
    else
        $(1)_HANDLER_OBJ :=
    endif

    # 5. NON_HANDLER_OBJ Logic
    $(1)_NON_HANDLER_OBJ := $$(filter-out $$($(1)_HANDLER_OBJ), $$($(1)_ALL_RELS))
    
    # 6. STARTUP_OBJ Logic
    ifneq ($$($(1)_ISR_FOUND),)
        $(1)_STARTUP_OBJ := _defaults/startup.rel
    else
        $(1)_STARTUP_OBJ := _defaults/startup_no_int.rel
    endif
    
    # 7. MEMMAP Logic
    ifneq ($(wildcard $(1)/memmap.ld),)
        $(1)_MEMMAP := $(1)/memmap.ld
    else
        $(1)_MEMMAP := _defaults/memmap.ld
    endif

    # 8. Linker Rule
    $(1)/$(notdir $(1)).ihx: $$($(1)_STARTUP_OBJ) $$($(1)_HANDLER_OBJ) $$($(1)_NON_HANDLER_OBJ) $$($(1)_MEMMAP) $(LIB_TARGET)
		@echo ""
		@echo "  NON_HANDLER_OBJ - $$($(1)_NON_HANDLER_OBJ)"
		@echo "  HANDLER_OBJ     - $$($(1)_HANDLER_OBJ)"
		@echo "  STARTUP_OBJ     - $$($(1)_STARTUP_OBJ)"
		@echo "  MEMMAP          - $$($(1)_MEMMAP)"
		@echo "  LIBRARY         - $(LIB_TARGET)"
		@$(GREP) "^\s*-[A-Za-z]" $$($(1)_MEMMAP) || true
		@echo ""
		$(SDCC) $(LDFLAGS) $$($(1)_STARTUP_OBJ) $$($(1)_HANDLER_OBJ) $$($(1)_NON_HANDLER_OBJ) $(LIB_TARGET) -Wl-u -Wl-f,$$($(1)_MEMMAP) -o $$@

    # 9. Binary/Disassembly Rule
    $(1)/$(notdir $(1)).bin: $(1)/$(notdir $(1)).ihx
		@echo ""
		@echo ">> Generating Binary and Disassembly $(1).bin and $(1).txs..."
		$(SDOBJCOPY) -I ihex -O binary $$< $$@
		@echo "$(Z80DASM) $(DASMFLAGS) $$@ 2> /dev/null > $$(@:%.bin=%.txs)"
		@$(Z80DASM) $(DASMFLAGS) $$@ 2> /dev/null | \
		awk ' \
		BEGIN { count = 0; } \
		/^[ \t]+nop[ \t]+;[0-9a-fA-F]{4}[ \t]+00.*$$$$/ { \
			buffer[count++] = $$$$0; \
			next; \
		} \
		{ \
			if (count > 3) { \
				print buffer[0]; \
				print "    ..."; \
				print buffer[count-1]; \
			} \
			else { for (i=0; i<count; i++) print buffer[i]; } \
			count = 0; \
			print $$$$0; \
			} \
		END { \
			if (count > 3) { \
				print buffer[0]; \
				print "    ..."; \
				print buffer[count-1]; \
			} \
			else { for (i=0; i<count; i++) print buffer[i]; } \
		}' > $$(@:%.bin=%.txs)
		@$(CP) $$@ ../sim/
		@echo "$$(shell $(TIMESTAMP_CMD))" > $$($(1)_STAMP)
		@echo "$$(shell $(TIMESTAMP_CMD)) ------------ built $(1).bin ------------"
		@echo ""

    # 10. The Public Folder Target
    .PHONY: $(1)
    $(1): $(1)/$(notdir $(1)).bin

endif

endef

# Iterate over ALL detected folders and evaluate the rules
$(foreach folder,$(ALL_DIRS),$(eval $(call DEFINE_RUN_RULES,$(folder))))

# -----------------------------------------------------------------------------
# Clean
# -----------------------------------------------------------------------------

# 1. Define the extensions to clean in one place
CLEAN_EXTS := *.asm *.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym *.txs

CLEAN_EXT_HEAD := $(firstword $(CLEAN_EXTS))
CLEAN_EXT_TAIL := $(wordlist 2,$(words $(CLEAN_EXTS)),$(CLEAN_EXTS))
FIND_CLEAN_EXTS := -name "$(CLEAN_EXT_HEAD)" $(foreach ext,$(CLEAN_EXT_TAIL),-o -name "$(ext)")

# 2. Use one recipe block for clean
clean:
	@echo ""
	@echo ">> Cleaning artifacts in sim folder..."
	$(RM) ../sim/*.bin
	@echo ""
	@echo ">> Cleaning artifacts in _defaults folder..."
	cd _defaults && $(RM) $(CLEAN_EXTS)
	@echo ""
	@echo ">> Cleaning artifacts in _library folder..."
	cd _library && $(RM) $(CLEAN_EXTS) $(LIB_NAME)
	@echo ""
	@echo ">> Cleaning timestamps.."
	@$(foreach folder,$(ALL_DIRS), echo "   cleaning $(folder) timestamps..."; $(RM) $(dir $(folder))*.stamp;)
	@echo ""
	@echo ">> Cleaning artifacts in code folders (recursive)..."
	@$(foreach folder,$(ALL_DIRS), \
		echo "   cleaning $(folder)"; \
		find $(folder) $(FIND_CLEAN_EXTS) | xargs $(RM); \
	)
	@echo "$$($(TIMESTAMP_CMD)) ------------ clean successful ------------"
	@echo ""
