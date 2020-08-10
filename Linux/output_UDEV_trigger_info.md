# 1. airprint on + ipp-usb不启动

 `$sudo udevadm trigger -v --subsystem-match=usb --attr-match=bInterfaceClass=07`<br>
 ` /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1`<br>
 ` /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.2`<br>
<br>
 `$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1`<br>
 ` looking at device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1':`<br>
 `   KERNEL=="1-2:1.1"`<br>
 `   SUBSYSTEM=="usb"`<br>
 `   DRIVER=="usblp"`<br>
 `   ATTR{bInterfaceProtocol}=="02"`<br>
 `   ATTR{bInterfaceSubClass}=="01"`<br>
 `   ATTR{supports_autosuspend}=="1"`<br>
 `   ATTR{bInterfaceClass}=="07"`<br>
 `   ATTR{bNumEndpoints}=="02"`<br>
 `   ATTR{ieee1284_id}=="MFG:XXXXX;MDL:MF746C PS3;CLS:PRINTER;DES:XXXXX MF746C PS3;``CID:CA_PS3_COLOR_OIP;CMD:LIPSLX,CPCA;PESP:V1;"`<br>
 `   ATTR{bInterfaceNumber}=="01"`<br>
 `   ATTR{authorized}=="1"`<br>
 `   ATTR{bAlternateSetting}==" 0"`<br>
<br>
 `$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.2`<br>
 ` looking at device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.2':`<br>
 `   KERNEL=="1-2:1.2"`<br>
 `   SUBSYSTEM=="usb"`<br>
 `   DRIVER=="usblp"`<br>
 `   ATTR{ieee1284_id}=="MFG:XXXXX;MDL:MF7xxC/7xxC FAX;CLS:PRINTER;DES:XXXXX MF7xxC/7xxC FAX;``CID:CA_FAX_OIP;CMD:LIPSLX,CPCA;PESP:V1;"`<br>
 `   ATTR{supports_autosuspend}=="1"`<br>
 `   ATTR{bInterfaceNumber}=="02"`<br>
 `   ATTR{bInterfaceProtocol}=="02"`<br>
 `   ATTR{bInterfaceSubClass}=="01"`<br>
 `   ATTR{bNumEndpoints}=="02"`<br>
 `   ATTR{bAlternateSetting}==" 0"`<br>
 `   ATTR{authorized}=="1"`<br>
 `   ATTR{bInterfaceClass}=="07"`<br>

# 2. airprint on + ipp-usb启动
 `$sudo udevadm trigger -v --subsystem-match=usb --attr-match=bInterfaceClass=07`<br>
 ` /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.0`<br>
 ` /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1`<br>
 ` /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.2`<br>
 <br>
 `$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.0`<br>
 ` looking at device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.0':`<br>
 `   KERNEL=="1-2:1.0"`<br>
 `   SUBSYSTEM=="usb"`<br>
 `   DRIVER=="usbfs"`<br>
 `   ATTR{bNumEndpoints}=="02"`<br>
 `   ATTR{bAlternateSetting}==" 1"`<br>
 `   ATTR{supports_autosuspend}=="0"`<br>
 `   ATTR{bInterfaceClass}=="07"`<br>
 `   ATTR{authorized}=="1"`<br>
 `   ATTR{bInterfaceProtocol}=="04"`<br>
 `   ATTR{bInterfaceSubClass}=="01"`<br>
 `   ATTR{bInterfaceNumber}=="00"`<br>
<br>
 `$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1`<br>
 ` looking at device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.1':`<br>
 `   KERNEL=="1-2:1.1"`<br>
 `   SUBSYSTEM=="usb"`<br>
 `   DRIVER=="usbfs"`<br>
 `   ATTR{bInterfaceSubClass}=="01"`<br>
 `   ATTR{bInterfaceProtocol}=="04"`<br>
 `   ATTR{bNumEndpoints}=="02"`<br>
 `   ATTR{supports_autosuspend}=="0"`<br>
 `   ATTR{authorized}=="1"`<br>
 `   ATTR{bInterfaceClass}=="07"`<br>
 `   ATTR{bAlternateSetting}==" 1"`<br>
 `   ATTR{bInterfaceNumber}=="01"`<br>
<br>
 `$sudo udevadm info -a -p /sys/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.2`<br>
 ` looking at device '/devices/pci0000:00/0000:00:14.0/usb1/1-2/1-2:1.2':`<br>
 `   KERNEL=="1-2:1.2"`<br>
 `   SUBSYSTEM=="usb"`<br>
 `   DRIVER==""`<br>
 `   ATTR{authorized}=="1"`<br>
 `   ATTR{bNumEndpoints}=="02"`<br>
 `   ATTR{bAlternateSetting}==" 0"`<br>
 `   ATTR{bInterfaceSubClass}=="01"`<br>
 `   ATTR{bInterfaceClass}=="07"`<br>
 `   ATTR{bInterfaceNumber}=="02"`<br>
 `   ATTR{bInterfaceProtocol}=="02"`<br>
 `   ATTR{supports_autosuspend}=="1"`<br>

# 3. 结论：
对照着USB interfaces来看，
ipp-usb启动的时候，将包含714且Alt=1的interface转成了devpath（三个devpath中都包含了class=7的属性）。
ipp-usb不启动的时候，保留Alt=0的interface转成了devpath（三个devpath中只有两个devpath中包含了class=7的属性）
 USB interfaces:<br>
   | Config | Interface | Alt | Class | SubClass | Proto |
   | :-: | :-: |:-: |:-: |:-: |:-: |
   | 1 | 0 | 0 | 255 | 0 | 255 |
   | 1 | 0 | 1 |  7  | 1 | 4 |
   | 1 | 1 | 0 |  7  | 1 | 2 |
   | 1 | 1 | 1 |  7  | 1 | 4 |
   | 1 | 2 | 0 |  7  | 1 | 2 |

 What about userspace (usbfs) drivers?
 When the driver is usbfs, it basically means a userspace (non-kernel) program is functioning as the driver. 