################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
bmpconfig.obj: ../bmpconfig.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/c6000_7.4.14/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/c6000_7.4.14/include" --include_path="../../../Include/MathLib" --include_path="../../../Include/DSPLib" --include_path="../../../Include/IMGLib" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="bmpconfig.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/c6000_7.4.14/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/c6000_7.4.14/include" --include_path="../../../Include/MathLib" --include_path="../../../Include/DSPLib" --include_path="../../../Include/IMGLib" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


