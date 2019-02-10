.PHONY: clean All

All:
	@echo "----------Building project:[ UOCOlimpics - Debug ]----------"
	@cd "UOCOlimpics" && "$(MAKE)" -f  "UOCOlimpics.mk"
clean:
	@echo "----------Cleaning project:[ UOCOlimpics - Debug ]----------"
	@cd "UOCOlimpics" && "$(MAKE)" -f  "UOCOlimpics.mk" clean
