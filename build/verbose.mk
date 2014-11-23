# Macros for controlling verbosity
# definition of verbose variable 'v' used to enable verbose output
# $(VERBOSE) expands to empty or @ to suppress echoing commands in recipes
# $(call,echo,text) conditionally outputs text if verbose is enabled

ifdef v
ECHO=echo
VERBOSE=
else
ECHO = #
VERBOSE=@
MAKE_ARGS += -s
endif

echo=$(ECHO $1)
