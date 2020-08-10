# 1. monitor
插入USB打印机后截取event信息<br>
`$sudo udevadmin monitor`  

# 2. trigger
想回放一些event的话，可以使用trigger, 下面命令可以用来搜索USB设备对应的devpath<br>
`$sudo udevadm trigger -v --subsystem-match=usb --attr-match=manufacturer=XXXXX` <br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4` 

`$sudo udevadm trigger -v --subsystem-match=usb`<br>
`...`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.0`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.1`<br>
`/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1/3-1.4/3-1.4.4/3-1.4.4.4/3-1.4.4.4:1.2`<br>
`...`


# 3. info 
查询USB信息<br>
`$sudo udevadm info -a -p $(udevadm info -q path -n /dev/usb/lp0)`

Ubuntu14.04, Debian8.11, Cent0s7.7, Fedora28之后的系统也可以直接用如下命令来获取USB信息。<br>
`$sudo udevadm info -a -n usb/lp0` <br>
`$sudo udevadm info -a /dev/usb/lp0` <br>

示例1<br>
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
    `ATTR{product}=="MF7xxC/7xxC"`<br>
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
    `ATTR{manufacturer}=="XXXXX"`<br>
    `ATTR{quirks}=="0x0"`<br>
    `ATTR{bMaxPower}=="2mA"`<br>
    `ATTR{bNumConfigurations}=="1"`<br>
    `ATTR{bDeviceClass}=="00"`<br>

  示例2<br>
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

# 4. test 
调试Device URI会触发哪些rule<br>
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
`ID_VENDOR=XXXXX`<br>
`ID_VENDOR_ENC=XXXXX`<br>
`ID_VENDOR_ID=04a9`<br>
`ID_MODEL=MF7xxC_7xxC`<br>
`ID_MODEL_ENC=MF7xxC\x2f7xxC`<br>
`ID_MODEL_ID=27fa`<br>
`ID_REVISION=0000`<br>
`ID_SERIAL=XXXXX_MF7xxC_7xxC_f4a997cf9d6c`<br>
`ID_SERIAL_SHORT=f4a997cf9d6c`<br>
`ID_BUS=usb`<br>
`ID_USB_INTERFACES=:ff00ff:070104:070102:`<br>
`TAGS=:systemd:`<br>
`SYSTEMD_WANTS=configure-printer@usb-002-056.service ipp-usb.service printer.target`<br>
`UDISKS_IGNORE=1`<br>
`USEC_INITIALIZED=73306599245`<br>
`Unload module index`<br>
`Unloaded link configuration context.`<br>

# 5. Other 
# 现存的issue：ipp-usb和厂商的USB Driver不能并存<br>