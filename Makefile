all: examples

examples:
	$(MAKE) -C $@

clean:
	$(MAKE) -C examples $@

.PHONY: all examples clean
