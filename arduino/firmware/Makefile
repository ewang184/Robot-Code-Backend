.PHONY: build upload deploy
BOARD = arduino:avr:uno
PORT = /dev/ttyUSB0

deploy:
	$(MAKE) SKETCH=src upload

upload: build
	@arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(SKETCH)

build:
	@arduino-cli compile -b $(BOARD) $(SKETCH)
