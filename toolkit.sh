#!/bin/bash

QEMU_CMD='qemu-system-x86_64'															
ZIP_CMD='zip'																			
MINIX_MOUNT_CMD='mount -t minix -o rw,loop,offset=1483776'								

MINIX_IMG='minix203.img'
MOUNT_DIR='minix_mnt'
MINIX_USR_DIR='source'

if test $UID -ne 0
then
	echo 'Permission denied. Run with superuser permissions.'
	exit 1
fi

mkdir -p $MOUNT_DIR

run_minix()
{
	$QEMU_CMD $MINIX_IMG
}

mount_image()
{
	if ! mount | grep "$PWD/$MINIX_IMG" > /dev/null
	then
		$MINIX_MOUNT_CMD $MINIX_IMG $MOUNT_DIR
	fi
}

umount_image()
{
	if mount | grep "$PWD/$MINIX_IMG" > /dev/null
	then
		while ! umount "$PWD/$MINIX_IMG"
		do
			echo "MInix is busy. Press any ket to retry."
			read
		done
	fi
}

sync_files()
{
	rm -rf $MOUNT_DIR/src
	rm -rf $MOUNT_DIR/include
	rm -rf $MOUNT_DIR/local/dev
	cp -R  $MINIX_USR_DIR/src $MOUNT_DIR/src
	cp -R  $MINIX_USR_DIR/include $MOUNT_DIR/include
	cp -R  $MINIX_USR_DIR/dev $MOUNT_DIR/local/dev
	chown -R root $MOUNT_DIR/src
	chown -R root $MOUNT_DIR/include
	chown -R root $MOUNT_DIR/local/dev
}

echo

while true
do
	echo
	echo 	"== 1) Run MINIX"
	echo 	"== 2) Mount filesytem"
	echo 	"== 3) Unmount filesystem"
	echo 	"== 4) Sync files"
	echo 	"== 5) Sync files and run"
	echo 	"== q) Exit"
	echo -n	"== Choice: "; read CHOICE

	clear

	case $CHOICE in
		"1")
			run_minix
			;;
		"2")
			mount_image
			;;
		"3")
			umount_image
			;;
		"4")
			mount_image
			sync_files
			umount_image
			;;
		"5")
			mount_image
			sync_files
			umount_image
			run_minix
			;;
		"q")
			echo "-> Sleeeeeeeeeep"
			break
			;;
	esac
done

umount_image