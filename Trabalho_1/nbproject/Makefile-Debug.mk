#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Q4/1menuBubble.o \
	${OBJECTDIR}/Q4/2menuInsertion.o \
	${OBJECTDIR}/Q4/3menuMerge.o \
	${OBJECTDIR}/Q4/4menuQuick.o \
	${OBJECTDIR}/Q4/5menuHeap.o \
	${OBJECTDIR}/Q4/questao4.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/questao1.o \
	${OBJECTDIR}/questao2.o \
	${OBJECTDIR}/questao3.o \
	${OBJECTDIR}/questao5.o


# C Compiler Flags
CFLAGS=-lm

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lm

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trab1_cal

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trab1_cal: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trab1_cal ${OBJECTFILES} ${LDLIBSOPTIONS} -lm

${OBJECTDIR}/Q4/1menuBubble.o: nbproject/Makefile-${CND_CONF}.mk Q4/1menuBubble.c 
	${MKDIR} -p ${OBJECTDIR}/Q4
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Q4/1menuBubble.o Q4/1menuBubble.c

${OBJECTDIR}/Q4/2menuInsertion.o: nbproject/Makefile-${CND_CONF}.mk Q4/2menuInsertion.c 
	${MKDIR} -p ${OBJECTDIR}/Q4
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Q4/2menuInsertion.o Q4/2menuInsertion.c

${OBJECTDIR}/Q4/3menuMerge.o: nbproject/Makefile-${CND_CONF}.mk Q4/3menuMerge.c 
	${MKDIR} -p ${OBJECTDIR}/Q4
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Q4/3menuMerge.o Q4/3menuMerge.c

${OBJECTDIR}/Q4/4menuQuick.o: nbproject/Makefile-${CND_CONF}.mk Q4/4menuQuick.c 
	${MKDIR} -p ${OBJECTDIR}/Q4
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Q4/4menuQuick.o Q4/4menuQuick.c

${OBJECTDIR}/Q4/5menuHeap.o: nbproject/Makefile-${CND_CONF}.mk Q4/5menuHeap.c 
	${MKDIR} -p ${OBJECTDIR}/Q4
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Q4/5menuHeap.o Q4/5menuHeap.c

${OBJECTDIR}/Q4/questao4.o: nbproject/Makefile-${CND_CONF}.mk Q4/questao4.c 
	${MKDIR} -p ${OBJECTDIR}/Q4
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Q4/questao4.o Q4/questao4.c

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/questao1.o: nbproject/Makefile-${CND_CONF}.mk questao1.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/questao1.o questao1.c

${OBJECTDIR}/questao2.o: nbproject/Makefile-${CND_CONF}.mk questao2.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/questao2.o questao2.c

${OBJECTDIR}/questao3.o: nbproject/Makefile-${CND_CONF}.mk questao3.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/questao3.o questao3.c

${OBJECTDIR}/questao5.o: nbproject/Makefile-${CND_CONF}.mk questao5.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/questao5.o questao5.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trab1_cal

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
