#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c ../../Maestro/Laboratorio3.1.Maestro.X/ADC_CONVERTER.c ../../Maestro/Laboratorio3.1.Maestro.X/BCD_CONVERTER_DISPLAY.c ../../Maestro/Laboratorio3.1.Maestro.X/BCH_CONVERTER_DISPLAY.c ../../Maestro/Laboratorio3.1.Maestro.X/BTD_CONVERTER.c ../../Maestro/Laboratorio3.1.Maestro.X/IO_CONFIG.c ../../Maestro/Laboratorio3.1.Maestro.X/LCD.c ../../Maestro/Laboratorio3.1.Maestro.X/OSCILADOR.c ../../Maestro/Laboratorio3.1.Maestro.X/PRINT_SERIAL.c ../../Maestro/Laboratorio3.1.Maestro.X/SPI.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1 ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1 ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1 ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1 ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1 ${OBJECTDIR}/_ext/2091300459/LCD.p1 ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1 ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1 ${OBJECTDIR}/_ext/2091300459/SPI.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/main.p1.d ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1.d ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1.d ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1.d ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1.d ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1.d ${OBJECTDIR}/_ext/2091300459/LCD.p1.d ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1.d ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1.d ${OBJECTDIR}/_ext/2091300459/SPI.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1 ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1 ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1 ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1 ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1 ${OBJECTDIR}/_ext/2091300459/LCD.p1 ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1 ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1 ${OBJECTDIR}/_ext/2091300459/SPI.p1

# Source Files
SOURCEFILES=main.c ../../Maestro/Laboratorio3.1.Maestro.X/ADC_CONVERTER.c ../../Maestro/Laboratorio3.1.Maestro.X/BCD_CONVERTER_DISPLAY.c ../../Maestro/Laboratorio3.1.Maestro.X/BCH_CONVERTER_DISPLAY.c ../../Maestro/Laboratorio3.1.Maestro.X/BTD_CONVERTER.c ../../Maestro/Laboratorio3.1.Maestro.X/IO_CONFIG.c ../../Maestro/Laboratorio3.1.Maestro.X/LCD.c ../../Maestro/Laboratorio3.1.Maestro.X/OSCILADOR.c ../../Maestro/Laboratorio3.1.Maestro.X/PRINT_SERIAL.c ../../Maestro/Laboratorio3.1.Maestro.X/SPI.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F887
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1: ../../Maestro/Laboratorio3.1.Maestro.X/ADC_CONVERTER.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1 ../../Maestro/Laboratorio3.1.Maestro.X/ADC_CONVERTER.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.d ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1: ../../Maestro/Laboratorio3.1.Maestro.X/BCD_CONVERTER_DISPLAY.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1 ../../Maestro/Laboratorio3.1.Maestro.X/BCD_CONVERTER_DISPLAY.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.d ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1: ../../Maestro/Laboratorio3.1.Maestro.X/BCH_CONVERTER_DISPLAY.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1 ../../Maestro/Laboratorio3.1.Maestro.X/BCH_CONVERTER_DISPLAY.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.d ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1: ../../Maestro/Laboratorio3.1.Maestro.X/BTD_CONVERTER.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1 ../../Maestro/Laboratorio3.1.Maestro.X/BTD_CONVERTER.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.d ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1: ../../Maestro/Laboratorio3.1.Maestro.X/IO_CONFIG.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1 ../../Maestro/Laboratorio3.1.Maestro.X/IO_CONFIG.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.d ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/LCD.p1: ../../Maestro/Laboratorio3.1.Maestro.X/LCD.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/LCD.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/LCD.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/LCD.p1 ../../Maestro/Laboratorio3.1.Maestro.X/LCD.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/LCD.d ${OBJECTDIR}/_ext/2091300459/LCD.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/LCD.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1: ../../Maestro/Laboratorio3.1.Maestro.X/OSCILADOR.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1 ../../Maestro/Laboratorio3.1.Maestro.X/OSCILADOR.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.d ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1: ../../Maestro/Laboratorio3.1.Maestro.X/PRINT_SERIAL.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1 ../../Maestro/Laboratorio3.1.Maestro.X/PRINT_SERIAL.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.d ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/SPI.p1: ../../Maestro/Laboratorio3.1.Maestro.X/SPI.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/SPI.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/SPI.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/SPI.p1 ../../Maestro/Laboratorio3.1.Maestro.X/SPI.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/SPI.d ${OBJECTDIR}/_ext/2091300459/SPI.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/SPI.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1: ../../Maestro/Laboratorio3.1.Maestro.X/ADC_CONVERTER.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1 ../../Maestro/Laboratorio3.1.Maestro.X/ADC_CONVERTER.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.d ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/ADC_CONVERTER.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1: ../../Maestro/Laboratorio3.1.Maestro.X/BCD_CONVERTER_DISPLAY.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1 ../../Maestro/Laboratorio3.1.Maestro.X/BCD_CONVERTER_DISPLAY.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.d ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/BCD_CONVERTER_DISPLAY.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1: ../../Maestro/Laboratorio3.1.Maestro.X/BCH_CONVERTER_DISPLAY.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1 ../../Maestro/Laboratorio3.1.Maestro.X/BCH_CONVERTER_DISPLAY.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.d ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/BCH_CONVERTER_DISPLAY.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1: ../../Maestro/Laboratorio3.1.Maestro.X/BTD_CONVERTER.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1 ../../Maestro/Laboratorio3.1.Maestro.X/BTD_CONVERTER.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.d ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/BTD_CONVERTER.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1: ../../Maestro/Laboratorio3.1.Maestro.X/IO_CONFIG.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1 ../../Maestro/Laboratorio3.1.Maestro.X/IO_CONFIG.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.d ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/IO_CONFIG.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/LCD.p1: ../../Maestro/Laboratorio3.1.Maestro.X/LCD.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/LCD.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/LCD.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/LCD.p1 ../../Maestro/Laboratorio3.1.Maestro.X/LCD.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/LCD.d ${OBJECTDIR}/_ext/2091300459/LCD.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/LCD.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1: ../../Maestro/Laboratorio3.1.Maestro.X/OSCILADOR.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1 ../../Maestro/Laboratorio3.1.Maestro.X/OSCILADOR.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.d ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/OSCILADOR.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1: ../../Maestro/Laboratorio3.1.Maestro.X/PRINT_SERIAL.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1 ../../Maestro/Laboratorio3.1.Maestro.X/PRINT_SERIAL.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.d ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/PRINT_SERIAL.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2091300459/SPI.p1: ../../Maestro/Laboratorio3.1.Maestro.X/SPI.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2091300459" 
	@${RM} ${OBJECTDIR}/_ext/2091300459/SPI.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2091300459/SPI.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/2091300459/SPI.p1 ../../Maestro/Laboratorio3.1.Maestro.X/SPI.c 
	@-${MV} ${OBJECTDIR}/_ext/2091300459/SPI.d ${OBJECTDIR}/_ext/2091300459/SPI.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2091300459/SPI.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -mrom=default,-1f00-1ffe -mram=default,-0-0,-70-70,-80-80,-f0-f0,-100-100,-170-170,-180-180,-1e5-1f0  $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/Laboratorio3.1.Esclavo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
