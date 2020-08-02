SUMMARY = "rgb2yuv"
SECTION = "rgb2yuv"
DEPENDS = ""
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

SRC_URI = "file://rgb2yuv-${PV}.tar.gz"

S = "${WORKDIR}/rgb2yuv-${PV}"

inherit autotools
# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""
