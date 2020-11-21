
leds_pb2.py: leds.pb.c
leds.pb.c: leds.proto
	python ../nanopb/generator/nanopb_generator.py $<
	protoc --python_out=. $<

.PHONY: clean
clean:
	rm -f leds.pb.* leds_pb2.py
