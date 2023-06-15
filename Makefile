#################
## DIRECTORIES ##
#################

TARGET_DIR  =   ./target
DEB_DIR     =   $(TARGET_DIR)/debug
REL_DIR     =   $(TARGET_DIR)/release
SOURCE_DIR  =   ./src
INC_DIR     =   


####################
## COMPILER FLAGS ##
####################

CC          =   gcc
CFLAGS      =   -Wall -Wextra -w -g
LDFLAGS     =   
CXXFLAGS    =   


#############
## TARGETS ##
#############

PROJECT     =   $(notdir $(shell pwd))
DEB_TARGET  =   $(DEB_DIR)/$(PROJECT)
VERSION     =   0.1
REL_TARGET  =   $(REL_DIR)/$(PROJECT)$(VERSION)


###############################
## SOURCES, OBJECTS, HEADERS ##
###############################

SRCS        =   $(shell find . -name "*.c")
OBJS        =   $(addsuffix .o, $(basename $(notdir $(SRCS))))
DEB_OBJS    =   $(addprefix $(DEB_DIR)/, $(OBJS))
REL_OBJS    =   $(addprefix $(REL_DIR)/, $(OBJS))
HEADERS	    =   $(shell find . -name "*.h")


#################################
## DEBUG(NORMAL BUILD) SECTION ##
#################################

$(DEB_DIR)/%.o: $(SOURCE_DIR)/%.c | $(DEB_DIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -MMD -c $< -o $@

$(DEB_TARGET): $(DEB_OBJS)
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $@ $(DEB_OBJS) $(LDFLAGS)


#####################
## RELEASE SECTION ##
#####################

release: $(REL_TARGET)

$(REL_DIR)/%.o: $(SOURCE_DIR)/%.c | $(REL_DIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -MMD -c $< -o $@

$(REL_TARGET): $(REL_OBJS)
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $@ $(REL_OBJS) $(LDFLAGS)


#################
## CREATE DIRS ##
#################

$(DEB_DIR):
	@mkdir -p $(DEB_DIR)

$(REL_DIR):
	@mkdir -p $(REL_DIR)


############################
## CLEAN AND INCLUDE FUNC ##
############################

.PHONY: clean clean-rel
clean:
	@rm -rvf $(DEB_DIR)

clean-rel:
	@rm -rvf $(REL_DIR)

-include $(wildcard $(DEB_DIR)/*.d)
-include $(wildcard $(REL_DIR)/*.d)
