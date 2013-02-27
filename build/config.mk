PRODUCT_NAME=EchoJS
PRODUCT_VERSION=0.1

PRODUCT_RELEASE_NOTES_URL=http://toshokelectric.com/echojs/release_notes
PRODUCT_GITHUB_URL=https://github.com/toshok/echo-js
PRODUCT_EMAIL=toshok@toshokelectric.com
ORGANIZATION=com.toshokelectric


PRODUCT_name:=$(shell echo $(PRODUCT_NAME) | tr [:upper:] [:lower:])

PRODUCT_UTI=$(ORGANIZATION).$(PRODUCT_NAME)

# the place where we stuff everything
PRODUCT_INSTALL_ROOT=/Developer/$(PRODUCT_NAME)

# in the future this should really be the value for DIST_ROOT, so we can build packages without trashing what's in PRODUCT_INSTALL_ROOT
#
#  DIST_ROOT=$(TOP)/dist
#
# but until then...
DIST_ROOT=$(PRODUCT_INSTALL_ROOT)

MKDIR=mkdir -p
INSTALL=install
CP=cp

CFLAGS=-g -O2 -Wall -I.

MIN_IOS_VERSION=5.0

IOSSIM_ARCH=-arch i386
IOSSIM_ARCH_FLAGS= -x objective-c
IOSSIM_TRIPLE=i386-apple-darwin
IOSSIM_ROOT=/Developer/Platforms/iPhoneSimulator.platform/Developer
IOSSIM_BIN=$(IOSSIM_ROOT)/usr/bin
IOSSIM_SYSROOT=$(IOSSIM_ROOT)/SDKs/iPhoneSimulator5.0.sdk

IOSDEV_ARCH=-arch armv7
IOSDEV_ARCH_FLAGS=-mthumb -x objective-c
IOSDEV_TRIPLE=armv7-apple-darwin
IOSDEV_ROOT=/Developer/Platforms/iPhoneOS.platform/Developer
IOSDEV_BIN=$(IOSDEV_ROOT)/usr/bin
IOSDEV_SYSROOT=$(IOSDEV_ROOT)/SDKs/iPhoneOS5.0.sdk 

IOSSIM_CFLAGS=$(IOSSIM_ARCH) $(IOSSIM_ARCH_FLAGS) $(CFLAGS) -DIOS -isysroot $(IOSSIM_SYSROOT) -miphoneos-version-min=$(IOS_MIN_VERSION)
IOSDEV_CFLAGS=$(IOSDEV_ARCH) $(IOSDEV_ARCH_FLAGS) $(CFLAGS) -DIOS -isysroot $(IOSDEV_SYSROOT) -miphoneos-version-min=$(IOS_MIN_VERSION)

-include $(TOP)/build/config-local.mk