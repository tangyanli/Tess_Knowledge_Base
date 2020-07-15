# 插入USB打印机后截取event信息<br>
`$sudo udevadmin monitor `  

# 想回放一些event的话，可以使用trigger, 下面命令可以用来搜索USB设备对应的devpath<br>
`$sudo udevadm trigger -v --subsystem-match=usb --attr-match=manufacturer=Canon` <br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4` 

`$sudo udevadm trigger -v --subsystem-match=usb`<br>
`...`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.0`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.1`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.2`<br>
`...`


# 查询USB信息<br>
`$sudo udevadm info -a -p $(udevadm info -q path -n /dev/usb/lp0)`
## Ubuntu14.04, Debian8.11, Cent0s7.7, Fedora28之后的系统也可以直接用如下命令来获取USB信息。
`$sudo udevadm info -a -n usb/lp0` <br>
`$sudo udevadm info -a /dev/usb/lp0` <br>

***
`$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4`<br>
  `looking at device '/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4':`<br>
    `KERNEL=="3-1.4.4.4"`<br>
    `SUBSYSTEM=="usb"`<br>
    `DRIVER=="usb"`<br>
    `ATTR{busnum}=="3"`<br>
    `ATTR{bMaxPacketSize0}=="64"`<br>
    `ATTR{idVendor}=="04a9"`<br>
    `ATTR{bDeviceProtocol}=="00"`<br>
    `ATTR{avoid_reset_quirk}=="0"`<br>
    `ATTR{product}=="MF745C/746C"`<br>
    `ATTR{idProduct}=="27fa"`<br>
    `ATTR{removable}=="unknown"`<br>
    `ATTR{authorized}=="1"`<br>
    `ATTR{devnum}=="8"`<br>
    `ATTR{bConfigurationValue}=="1"`<br>
    `ATTR{speed}=="480"`<br>
    `ATTR{serial}=="f4a997cf9d6c"`<br>
    `ATTR{bcdDevice}=="0000"`<br>
    `ATTR{maxchild}=="0"`<br>
    `ATTR{bNumInterfaces}==" 3"`<br>
    `ATTR{bmAttributes}=="c0"`<br>
    `ATTR{devpath}=="1.4.4.4"`<br>
    `ATTR{urbnum}=="62"`<br>
    `ATTR{rx_lanes}=="1"`<br>
    `ATTR{version}==" 2.10"`<br>
    `ATTR{bDeviceSubClass}=="00"`<br>
    `ATTR{tx_lanes}=="1"`<br>
    `ATTR{ltm_capable}=="no"`<br>
    `ATTR{configuration}==""`<br>
    `ATTR{manufacturer}=="Canon"`<br>
    `ATTR{quirks}=="0x0"`<br>
    `ATTR{bMaxPower}=="2mA"`<br>
    `ATTR{bNumConfigurations}=="1"`<br>
    `ATTR{bDeviceClass}=="00"`<br>

  `looking at parent device '/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4':`<br>
    `KERNELS=="3-1.4.4"`<br>
    `SUBSYSTEMS=="usb"`<br>
    `DRIVERS=="usb"`<br>
    `ATTRS{bDeviceClass}=="09"`<br>
    `ATTRS{quirks}=="0x4000"`<br>
    `ATTRS{bDeviceSubClass}=="00"`<br>
    `ATTRS{busnum}=="3"`<br>
    `ATTRS{bConfigurationValue}=="1"`<br>
    `ATTRS{bNumInterfaces}==" 1"`<br>
    `ATTRS{idProduct}=="0101"`<br>
    `ATTRS{tx_lanes}=="1"`<br>
    `ATTRS{bmAttributes}=="e0"`<br>
    `ATTRS{ltm_capable}=="no"`<br>
    `ATTRS{urbnum}=="35"`<br>
    `ATTRS{bDeviceProtocol}=="01"`<br>
    `ATTRS{devnum}=="6"`<br>
    `ATTRS{devpath}=="1.4.4"`<br>
    `ATTRS{rx_lanes}=="1"`<br>
    `ATTRS{speed}=="480"`<br>
    `ATTRS{bMaxPacketSize0}=="64"`<br>
    `ATTRS{bNumConfigurations}=="1"`<br>
    `ATTRS{product}=="USB 2.0 Hub"`<br>
    `ATTRS{authorized}=="1"`<br>
    `ATTRS{bcdDevice}=="0111"`<br>
    `ATTRS{bMaxPower}=="100mA"`<br>
    `ATTRS{avoid_reset_quirk}=="0"`<br>
    `ATTRS{version}==" 2.00"`<br>
    `ATTRS{configuration}==""`<br>
    `ATTRS{removable}=="unknown"`<br>
    `ATTRS{idVendor}=="1a40"`<br>
    `ATTRS{maxchild}=="4"`<br>

***
`$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.0` <br>
  `looking at device '/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.0':`<br>
    `KERNEL=="3-1.4.4.4:1.0"`<br>
    `SUBSYSTEM=="usb"`<br>
    `DRIVER=="usbfs"`<br>
    `ATTR{bInterfaceProtocol}=="04"`<br>
    `ATTR{bAlternateSetting}==" 1"`<br>
    `ATTR{supports_autosuspend}=="1"`<br>
    `ATTR{authorized}=="1"`<br>
    `ATTR{bInterfaceClass}=="07"`<br>
    `ATTR{bInterfaceSubClass}=="01"`<br>
    `ATTR{bInterfaceNumber}=="00"`<br>
    `ATTR{bNumEndpoints}=="02"`<br>

***
`$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.1`<br>
  `looking at device '/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.1':` <br>
    `KERNEL=="3-1.4.4.4:1.1"`<br>
    `SUBSYSTEM=="usb"`<br>
    `DRIVER=="usbfs"`<br>
    `ATTR{bInterfaceNumber}=="01"`<br>
    `ATTR{authorized}=="1"`<br>
    `ATTR{bInterfaceSubClass}=="01"`<br>
    `ATTR{bInterfaceClass}=="07"`<br>
    `ATTR{bInterfaceProtocol}=="04"`<br>
    `ATTR{bNumEndpoints}=="02"`<br>
    `ATTR{bAlternateSetting}==" 1"`<br>
    `ATTR{supports_autosuspend}=="1"`<br>

***
`$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.2`<br>
  `looking at device '/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.2':`<br>
    `KERNEL=="3-1.4.4.4:1.2"`<br>
    `SUBSYSTEM=="usb"`<br>
    `DRIVER==""`<br>
    `ATTR{authorized}=="1"`<br>
    `ATTR{bInterfaceProtocol}=="02"`<br>
    `ATTR{bInterfaceSubClass}=="01"`<br>
    `ATTR{bInterfaceClass}=="07"`<br>
    `ATTR{bAlternateSetting}==" 0"`<br>
    `ATTR{bInterfaceNumber}=="02"`<br>
    `ATTR{bNumEndpoints}=="02"`<br>
    `ATTR{supports_autosuspend}=="1"`<br>


# 调试Device URI会触发哪些rule<br>
`$sudo udevadm test /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2.4/2-2.4.4/2-2.4.4.4`

`Parsed configuration file /usr/lib/systemd/network/99-default.link`<br>
`Created link configuration context.`<br>
`Reading rules file: /usr/lib/udev/rules.d/01-md-raid-creating.rules`<br>
`Reading rules file: /usr/lib/udev/rules.d/...`<br>
`Reading rules file: /usr/lib/udev/rules.d/71-ipp-usb.rules`<br>
`Reading rules file: /usr/lib/udev/rules.d/...rules`<br>
`Rules contain 393216 bytes tokens (32768 * 12 bytes), 32935 bytes strings`<br>
`26823 strings (219696 bytes), 23679 de-duplicated (189906 bytes), 3145 trie nodes used`<br>
`Invalid inotify descriptor.`<br>
`Starting 'mtp-probe /sys/devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2.4/2-2.4.4/2-2.4.4.4 2 56'`<br>
`'mtp-probe /sys/devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2.4/2-2.4.4/2-2.4.4.4 2 56'(out) '0'`<br>
`Process 'mtp-probe /sys/devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2.4/2-2.4.4/2-2.4.4.4 2 56' succeeded.`<br>
`DEVPATH=/devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2.4/2-2.4.4/2-2.4.4.4`<br>
`DEVNAME=/dev/bus/usb/002/056`<br>
`DEVTYPE=usb_device`<br>
`DRIVER=usb<br>`
`PRODUCT=4a9/27fa/0`<br>
`TYPE=0/0/0`<br>
`BUSNUM=002`<br>
`DEVNUM=056`<br>
`MAJOR=189`<br>
`MINOR=183`<br>
`ACTION=add`<br>
`SUBSYSTEM=usb`<br>
`ID_VENDOR=Canon`<br>
`ID_VENDOR_ENC=Canon`<br>
`ID_VENDOR_ID=04a9`<br>
`ID_MODEL=MF745C_746C`<br>
`ID_MODEL_ENC=MF745C\x2f746C`<br>
`ID_MODEL_ID=27fa`<br>
`ID_REVISION=0000`<br>
`ID_SERIAL=Canon_MF745C_746C_f4a997cf9d6c`<br>
`ID_SERIAL_SHORT=f4a997cf9d6c`<br>
`ID_BUS=usb`<br>
`ID_USB_INTERFACES=:ff00ff:070104:070102:`<br>
`TAGS=:systemd:`<br>
`SYSTEMD_WANTS=configure-printer@usb-002-056.service ipp-usb.service printer.target`<br>
`UDISKS_IGNORE=1`<br>
`USEC_INITIALIZED=73306599245`<br>
`Unload module index`<br>
`Unloaded link configuration context.`<br>

# 现存的issue：ipp-usb和厂商的USB Driver不能并存<br>
https://lists.debian.org/debian-printing/2019/02/msg00014.html<br>
下面是Monitor截取到的消息。<br>
## ipp-usb Enable + plug USB
`tess@tess:~$ udevadm monitor`<br>
`monitor will print the received events for:`<br>
`UDEV - the event which udev sends out after rule processing`<br>
`KERNEL - the kernel uevent`<br>
`KERNEL[712.865384] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`KERNEL[712.873505] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`KERNEL[712.873552] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[712.875133] add      /class/usbmisc (class)`<br>
`KERNEL[712.875203] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`KERNEL[712.875237] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[712.875263] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [712.876037] add      /class/usbmisc (class)`<br>
`KERNEL[712.876651] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`KERNEL[712.876687] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`KERNEL[712.876722] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [712.890937] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`KERNEL[712.891555] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`KERNEL[712.891594] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[712.891703] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`KERNEL[712.891729] remove   /usbmisc (class)`<br>
`KERNEL[712.891752] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [712.894321] remove   /usbmisc (class)`<br>
`UDEV  [712.898915] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [712.898961] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`UDEV  [712.899654] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [712.901534] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`UDEV  [712.901793] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`UDEV  [712.903325] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [712.903877] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [712.910785] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [712.912171] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`UDEV  [712.913093] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [712.914086] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`UDEV  [712.914943] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
## ipp-usb Enable + unplug USB
`KERNEL[871.039893] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`KERNEL[871.040009] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`KERNEL[871.040089] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[871.040169] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[871.040241] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`KERNEL[871.040964] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`KERNEL[871.041090] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [871.046270] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`UDEV  [871.046865] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [871.047567] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [871.049258] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`UDEV  [871.050179] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [871.051788] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [871.052699] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
## ipp-usb Disable + plug USB
`tess@tess:~$ udevadm monitor`<br>
`monitor will print the received events for:`<br>
`UDEV - the event which udev sends out after rule processing`<br>
`KERNEL - the kernel uevent`<br>
`KERNEL[933.597199] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`KERNEL[933.600109] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`KERNEL[933.600509] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[933.601874] add      /class/usbmisc (class)`<br>
`KERNEL[933.602081] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`KERNEL[933.602193] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[933.602279] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`KERNEL[933.604060] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`KERNEL[933.604177] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`KERNEL[933.604291] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [933.605280] add      /class/usbmisc (class)`<br>
`UDEV  [933.620688] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [933.624520] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [933.625644] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [933.629062] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`UDEV  [933.629108] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`UDEV  [933.630501] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [933.631768] add      /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`UDEV  [933.633334] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [933.653093] bind     /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>

## ipp-usb Disable + unplug USB
`KERNEL[962.248869] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`KERNEL[962.249063] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`KERNEL[962.249154] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[962.249240] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`KERNEL[962.249384] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`KERNEL[962.249462] remove   /usbmisc (class)`<br>
`KERNEL[962.249530] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`KERNEL[962.249613] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`KERNEL[962.250226] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [962.253137] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.0 (usb)`<br>
`UDEV  [962.253948] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1/usbmisc/lp0 (usbmisc)`<br>
`UDEV  [962.254994] remove   /usbmisc (class)`<br>
`UDEV  [962.255052] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2/usbmisc/lp1 (usbmisc)`<br>
`UDEV  [962.256384] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [962.257035] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [962.258249] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.1 (usb)`<br>
`UDEV  [962.258573] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2/2-2:1.2 (usb)`<br>
`UDEV  [962.259612] unbind   /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
`UDEV  [962.260270] remove   /devices/pci0000:00/0000:00:14.0/usb2/2-2 (usb)`<br>
