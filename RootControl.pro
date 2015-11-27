TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += STM32F103VC STM32F10X_HD SYSTEM_LIB SUPPORT_CPLUSPLUS USE_STDPERIPH_DRIVER __ASSEMBLY__ __FPU_USED=0 __FPU_PRESENT=0


INCLUDEPATH += $$PWD/CoOS/kernel/ \
		$$PWD/CoOS/portable/ \
		$$PWD/GLCD \
		$$PWD/cmsis_boot \
		$$PWD/cmsis \
		$$PWD/stm_lib/inc \
		$$PWD/TouchPanel

SOURCES += main.cpp \
    brainRoot.cpp \
    CoOSMbox.cpp \
    cothread.cpp \
    display.cpp \
    sensClock.cpp \
    sensDummy.cpp \
    sensHumidity.cpp \
    sensor.cpp \
    thread.cpp \
    touchsensor.cpp \
    wgVerGauge.cpp \
    widget.cpp \
    EXTIset.c \
    cmsis_boot/system_stm32f10x.c \
    cmsis_boot/startup/startup_stm32f10x_hd.c \
    CoOS/kernel/core.c \
    CoOS/kernel/event.c \
    CoOS/kernel/flag.c \
    CoOS/kernel/hook.c \
    CoOS/kernel/kernelHeap.c \
    CoOS/kernel/mbox.c \
    CoOS/kernel/mm.c \
    CoOS/kernel/mutex.c \
    CoOS/kernel/queue.c \
    CoOS/kernel/sem.c \
    CoOS/kernel/serviceReq.c \
    CoOS/kernel/task.c \
    CoOS/kernel/time.c \
    CoOS/kernel/timer.c \
    CoOS/kernel/utility.c \
    CoOS/portable/GCC/port.c \
    CoOS/portable/arch.c \
    GLCD/AsciiLib.c \
    GLCD/GLCD.c \
    GLCD/HzLib.c \
    stm_lib/src/misc.c \
    stm_lib/src/stm32f10x_exti.c \
    stm_lib/src/stm32f10x_flash.c \
    stm_lib/src/stm32f10x_fsmc.c \
    stm_lib/src/stm32f10x_gpio.c \
    stm_lib/src/stm32f10x_i2c.c \
    stm_lib/src/stm32f10x_pwr.c \
    stm_lib/src/stm32f10x_rcc.c \
    stm_lib/src/stm32f10x_rtc.c \
    stm_lib/src/stm32f10x_spi.c \
    stm_lib/src/stm32f10x_tim.c \
    syscalls/syscalls.c \
    TouchPanel/TouchPanel.c

HEADERS += \
    brain.h \
    brainRoot.h \
    CoOSMbox.h \
    cothread.h \
    cothreadtest.h \
    display.h \
    emitter.h \
    EXTIset.h \
    listener.h \
    MBox.h \
    misc.h \
    sensClock.h \
    sensDummy.h \
    sensHumidity.h \
    sensor.h \
    thread.h \
    touchsensor.h \
    wgVerGauge.h \
    widget.h \
    cmsis/core_cm3.h \
    cmsis/core_cmFunc.h \
    cmsis/core_cmInstr.h \
    cmsis_boot/stm32f10x.h \
    cmsis_boot/stm32f10x_conf.h \
    cmsis_boot/system_stm32f10x.h \
    CoOS/kernel/coocox.h \
    CoOS/kernel/CoOS.h \
    CoOS/kernel/OsConfig.h \
    CoOS/kernel/OsCore.h \
    CoOS/kernel/OsError.h \
    CoOS/kernel/OsEvent.h \
    CoOS/kernel/OsFlag.h \
    CoOS/kernel/OsKernelHeap.h \
    CoOS/kernel/OsMM.h \
    CoOS/kernel/OsMutex.h \
    CoOS/kernel/OsQueue.h \
    CoOS/kernel/OsServiceReq.h \
    CoOS/kernel/OsTask.h \
    CoOS/kernel/OsTime.h \
    CoOS/kernel/OsTimer.h \
    CoOS/kernel/utility.h \
    CoOS/portable/OsArch.h \
    CoOS/OsConfig.h \
    GLCD/AsciiLib.h \
    GLCD/GLCD.h \
    GLCD/HzLib.h \
    stm_lib/inc/misc.h \
    stm_lib/inc/stm32f10x_exti.h \
    stm_lib/inc/stm32f10x_flash.h \
    stm_lib/inc/stm32f10x_fsmc.h \
    stm_lib/inc/stm32f10x_gpio.h \
    stm_lib/inc/stm32f10x_i2c.h \
    stm_lib/inc/stm32f10x_pwr.h \
    stm_lib/inc/stm32f10x_rcc.h \
    stm_lib/inc/stm32f10x_rtc.h \
    stm_lib/inc/stm32f10x_spi.h \
    stm_lib/inc/stm32f10x_tim.h \
    TouchPanel/TouchPanel.h

