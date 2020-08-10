https://lists.debian.org/debian-printing/2019/02/msg00014.html<br>
下面是Monitor截取到的消息。<br>

# 1. Plug USB
## 1.1 ipp-usb Enable
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

## ipp-usb Disable
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
# 2. Unplug USB
## ipp-usb Enable
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

## ipp-usb Disable
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
