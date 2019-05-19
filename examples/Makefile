dirs= $(wildcard */.)
cleandirs= $(dirs:%=clean-%)

all: $(dirs)

$(dirs):
	$(MAKE) -C $@

clean: $(cleandirs)

$(cleandirs):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(dirs)
.PHONY: subdirs $(cleandirs)
.PHONY: all clean
