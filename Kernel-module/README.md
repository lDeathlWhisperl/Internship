# <p align="center"> internship--kernel-module </p>
## Инструкция по запуску

```bash
make
sudo insmod hello.ko    # установка модуля в ядро
sudo lsmod | grep hello # проверка, что модуль загружен
sudo dmesg | grep Hello # вывод сообщения
sudo rmmod hello        # удаление модуля из ядра
make clean
```   
