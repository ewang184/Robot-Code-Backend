.PHONY: build upload deploy
BOARD = arduino:avr:uno
PORT = /dev/ttyUSB0

deploy:
	@read -p 'Enter name of sketch to deploy: ' result && $(MAKE) SKETCH=$$result upload

upload: build
	@arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(SKETCH)

build:
	@arduino-cli compile -b $(BOARD) $(SKETCH)
