unix {
    DEFINES += __UNIX__

    exists("/Applications/Launchpad.app") {
        SystemType=Mac
        DEFINES +=  __PLATFORM_MAC__  \
                    __FREEBSD__
    } else {
        UNAME=$$system(cat /etc/issue)
        contains(UNAME, Ubuntu) {
            SystemType=Ubuntu
            DEFINES += __PLATFORM_UBUNTU__
        }

        contains(UNAME, Debian): {
            SystemType=Debian
            DEFINES += __PLATFORM_DEBIAN__
        }
    }
}

win32 {
    SystemType=Windows
    DEFINES += __PLATFORM_WIN__
}


CONFIG(release, debug|release) {
    BuildType=release
    DEFINES += __RELEASE
    CONFIG += warn_off
} else {
    BuildType=debug
    DEFINES += __DEBUG
}

INTERMEDIATE_DIR = $$PWD/../Intermediate/$$BuildType

DESTDIR         = $$PWD/../RunImage/$$BuildType
OUT_PWD         = $$INTERMEDIATE_DIR/$$TARGET
MOC_DIR         = $$INTERMEDIATE_DIR/$$TARGET
OBJECTS_DIR     = $$INTERMEDIATE_DIR/$$TARGET
RCC_DIR         = $$INTERMEDIATE_DIR/$$TARGET
