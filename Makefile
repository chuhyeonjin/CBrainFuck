.PHONY: all clean
 
all:
	@$(MAKE) -C src

clean:
	@rm -rf build/
	@mkdir build
