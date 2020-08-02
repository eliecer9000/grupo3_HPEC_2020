#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

SUMMARY = "rgb2yuv_intrinsics"
SECTION = "rgb2yuv_intrinsics"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://rgb2yuv-intrinsics-${PV}.tar.gz"

S = "${WORKDIR}/rgb2yuv-intrinsics-${PV}"

inherit autotools
# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""
