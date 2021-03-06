TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = RootControl
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
    TouchPanel/TouchPanel.c \
    debug.cpp \
    stm_lib/src/stm32f10x_usart.c \
    i2c.c \
    wg2dplot.cpp \
    actuator.cpp \
    acthumi.cpp \
    stm_lib/src/stm32f10x_bkp.c \
    screen.cpp \
    display.cpp \
    wgnavscreens.cpp \
    wglabel.cpp \
    wgindicator.cpp \
    sdcard.cpp \
    SDCard/SD_Card/sdio_sd.c \
    SDCard/FATFS/src/option/syscall.c \
    SDCard/FATFS/src/diskio.c \
    SDCard/FATFS/src/ff.c \
    stm_lib/src/stm32f10x_sdio.c \
    stm_lib/src/stm32f10x_adc.c \
    stm_lib/src/stm32f10x_can.c \
    stm_lib/src/stm32f10x_cec.c \
    stm_lib/src/stm32f10x_crc.c \
    stm_lib/src/stm32f10x_dac.c \
    stm_lib/src/stm32f10x_dbgmcu.c \
    stm_lib/src/stm32f10x_dma.c \
    stm_lib/src/stm32f10x_iwdg.c \
    stm_lib/src/stm32f10x_wwdg.c \
    sdfile.cpp \
    acttemp.cpp \
    actled.cpp

HEADERS += \
    brain.h \
    brainRoot.h \
    CoOSMbox.h \
    cothread.h \
    cothreadtest.h \
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
    TouchPanel/TouchPanel.h \
    debug.h \
    stm_lib/inc/stm32f10x_usart.h \
    i2c.h \
    wg2dplot.h \
    project.h \
    senspassthru.h \
    actuator.h \
    acttemp.h \
    acthumi.h \
    stm_lib/inc/stm32f10x_bkp.h \
    screen.h \
    display.h \
    wgnavscreens.h \
    wglabel.h \
    wgindicator.h \
    sdcard.h \
    SDCard/FATFS_V0.08A/src/diskio.h \
    SDCard/FATFS_V0.08A/src/ff.h \
    SDCard/FATFS_V0.08A/src/ffconf.h \
    SDCard/FATFS_V0.08A/src/integer.h \
    SDCard/SD_Card/sdio_sd.h \
    SDCard/stm32f10x_conf.h \
    SDCard/FATFS/src/diskio.h \
    SDCard/FATFS/src/ff.h \
    SDCard/FATFS/src/ffconf.h \
    SDCard/FATFS/src/integer.h \
    stm_lib/inc/stm32f10x_sdio.h \
    stm_lib/inc/stm32f10x_adc.h \
    stm_lib/inc/stm32f10x_can.h \
    stm_lib/inc/stm32f10x_cec.h \
    stm_lib/inc/stm32f10x_crc.h \
    stm_lib/inc/stm32f10x_dac.h \
    stm_lib/inc/stm32f10x_dbgmcu.h \
    stm_lib/inc/stm32f10x_dma.h \
    stm_lib/inc/stm32f10x_iwdg.h \
    stm_lib/inc/stm32f10x_wwdg.h \
    sdfile.h \
    rootcontrolsettings.h \
    actled.h
QMAKE_CXXFLAGS += -Ofast
QMAKE_POST_LINK = $$quote($$QMAKE_OBJCOPY -O binary $$OUT_PWD/$$DESTDIR/$$TARGET $$OUT_PWD/$$DESTDIR/"$$TARGET".bin)
