all:
	make -C nes-head
	make -C chr-to-bmp
	make -C extract-chr

.PHONY: clean
clean:
	make -C nes-head clean
	make -C chr-to-bmp clean
	make -C extract-chr clean
