
all:
	$(MAKE) -C proto
	$(MAKE) -C libopencm3
	$(MAKE) -C f4_proto

clean:
	$(MAKE) -C proto clean
	$(MAKE) -C f4_proto clean
